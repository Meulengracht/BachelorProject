/*
 * Physical Memory Manager for KUdos
 *
 * Copyright (C) 2003-2014 Juha Aatrokoski, Timo Lilja,
 *   Leena Salmela, Teemu Takanen, Aleksi Virtanen,
 *   Philip Meulengracht.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id: mm_phys.c,v 1.0 2003/03/27 11:38:16 philip Exp $
 *
 */

#include <multiboot.h>
#include <arch.h>
#include "vm/memory.h"
#include "lib/libc.h"
#include "kernel/stalloc.h"
#include "kernel/spinlock.h"
#include "kernel/interrupt.h"
#include "kernel/panic.h"

/* PMM Defines */
#define PMM_BLOCKS_PER_BYTE 0x8
#define PMM_BLOCK_SIZE 0x1000

 /* Memory Map */
uint64_t *_MemBitmap;
uint64_t BitMapSize;
uint64_t MemorySize;
uint64_t TotalBlocks;
uint64_t UsedBlocks;
uint64_t HighestPage;
spinlock_t *PhysMemLock;

/* Memory Bitmap Helpers */
void MemMap_SetBit(int64_t Bit)
{
	_MemBitmap[Bit / 64] |= (1 << (Bit % 64));
}

void MemMap_UnsetBit(int64_t Bit)
{
	_MemBitmap[Bit / 64] &= ~(1 << (Bit % 64));
}

int64_t MemMap_TestBit(int64_t Bit)
{
	return _MemBitmap[Bit / 64] & (1 << (Bit % 64));
}

void physmem_freeregion(uint64_t StartAddress, uint64_t Length)
{
	int64_t Align = (int64_t)(StartAddress / PMM_BLOCK_SIZE);
	int64_t Blocks = (int64_t)(Length / PMM_BLOCK_SIZE);
	int64_t i = (int64_t)StartAddress;

	/* Free Blocks */
	for(; Blocks > 0; Blocks--, i += PMM_BLOCK_SIZE)
	{
		/* Free it */
		MemMap_UnsetBit(Align++);
		UsedBlocks--;

		if(i > HighestPage)
			HighestPage = i;
	}

	/* Make sure first block is always used! */
	/* Allocs must never be 0 */
	MemMap_SetBit(0);
}

int64_t physmem_getframe()
{
	uint64_t i, j;

	/* Loop through bitmap */
	for(i = 0; i < TotalBlocks; i++)
	{
		if(_MemBitmap[i] != 0xFFFFFFFFFFFFFFFF)
		{
			for(j = 0; j < 64; j++)
			{
				int64_t Bit = 1 << j;

				if(!(_MemBitmap[i] & Bit))
					return (int64_t)(i * 8 * 8 + j);
			}
		}
	}

	/* End of Memory */
	return -1;
}

int64_t physmem_getframes(int64_t Count)
{
	uint64_t i, j, k;

	/* Sanity */
	if(Count == 0)
		return -1;

	if(Count == 1)
		return physmem_getframe();

	/* Loop through bitmap */
	for(i = 0; i < TotalBlocks; i++)
	{
		if(_MemBitmap[i] != 0xFFFFFFFFFFFFFFFF)
		{
			for(j = 0; j < 64; j++)
			{
				int64_t Bit = 1 << j;
				if(!(_MemBitmap[i] & Bit))
				{
					int64_t StartingBit = i * 64;
					int64_t Free = 0;
					StartingBit += Bit;

					/* Get the free bit in qword at index i */
					for(k = 0; k <= Count; k++)
					{
						/* Test if it is free */
						if(MemMap_TestBit(StartingBit + k) == 0)
							Free++;

						/* Did we have enough free blocks? */
						if(Free == Count)
							return (int64_t)(i * 8 * 8 + j);
					}
				}
			}
		}
	}

	/* End of Memory */
	return -1;
}

void physmem_init(void *BootInfo)
{
	multiboot_info_t *MbInfo = (multiboot_info_t*)BootInfo;
	uint64_t *MemPtr = (uint64_t*)(uint64_t)MbInfo->MemoryMapAddr;
	uint64_t Itr = 0, LastAddress = 0;
	
	/* Setup Memory Stuff */
	HighestPage = 0;
	MemorySize = MbInfo->MemoryHigh;
	MemorySize += MbInfo->MemoryLow;
	TotalBlocks = (MemorySize * 1024) / PAGE_SIZE;
	UsedBlocks = TotalBlocks;
	BitMapSize = TotalBlocks / PMM_BLOCKS_PER_BYTE;
	_MemBitmap = (uint64_t*)stalloc(BitMapSize);
	PhysMemLock = (spinlock_t*)stalloc(sizeof(spinlock_t));
	spinlock_reset(PhysMemLock);

	/* Set all memory as used, and use memory map to set free */
	memoryset(_MemBitmap, 0xF, BitMapSize);

	/* Physical Page Bitmap */
	kprintf("Memory Size: %u Kb\n", (uint32_t)MemorySize);

	/* Go through regions */
	for(Itr = (uint64_t)MemPtr; 
		Itr < ((uint64_t)MemPtr + MbInfo->MemoryMapLength);
		)
	{
		/* Get next member */
		mem_region_t *MemRegion = (mem_region_t*)Itr;

		/* Output */
		//kprintf("Memory Region: Address 0x%xL, Length 0x%xL, Type %u\n",
		//	MemRegion->BaseAddress, MemRegion->Length, MemRegion->Type);

		/* Is it free? */
		if(MemRegion->Type == MemType_Free)
			physmem_freeregion(MemRegion->BaseAddress, 
								MemRegion->Length);

		/* Advance by one structure */
		Itr += sizeof(mem_region_t);
	}

	/* Mark all memory up to the static allocation point as used */
	LastAddress = (physaddr_t)stalloc(1);
	stalloc_disable();

	for(Itr = physmem_allocblock(); Itr < LastAddress;)
		Itr = physmem_allocblock();

	/* Debug*/
	kprintf("New memory allocation starts at 0x%xl\n", Itr);
}

physaddr_t physmem_allocblock()
{
	/* Get spinlock */
	physaddr_t Addr = 0;
	interrupt_status_t intr_status = _interrupt_disable();
    spinlock_acquire(PhysMemLock);

	/* Sanity */
	if(UsedBlocks >= TotalBlocks)
	{
		/* PANIC AT THE DISCO ! */
		KERNEL_PANIC("Physical Manager >> OUT OF MEMORY");
	}

	/* Get a frame */
	int64_t Frame = physmem_getframe();

	if(Frame == -1)
	{
		/* PANIC AT THE DISCO ! */
		spinlock_release(PhysMemLock);
		KERNEL_PANIC("Physical Manager >> OUT OF MEMORY");
	}

	/* Mark it used */
	MemMap_SetBit(Frame);

	/* Release spinlock */
	spinlock_release(PhysMemLock);
    _interrupt_set_state(intr_status);

	/* Calculate Address */
	Addr = (physaddr_t)(Frame * PMM_BLOCK_SIZE);
	UsedBlocks++;

	return Addr;
}

void physmem_freeblock(void *Ptr)
{
	/* Calculate frame */
	uint64_t Addr = (uint64_t)Ptr;
	int64_t Frame = (int64_t)(Addr / PMM_BLOCK_SIZE);

	/* Get lock */
	interrupt_status_t intr_status = _interrupt_disable();
    spinlock_acquire(PhysMemLock);

    /* Free */
    MemMap_UnsetBit(Frame);

    /* Release spinlock */
	spinlock_release(PhysMemLock);
    _interrupt_set_state(intr_status);

    /* Stats */
    UsedBlocks--;
}

physaddr_t physmem_allocblocks(uint32_t Count)
{
	/* Get spinlock */
	physaddr_t Addr = 0, i;
	interrupt_status_t intr_status = _interrupt_disable();
    spinlock_acquire(PhysMemLock);

	/* Sanity */
	if(UsedBlocks >= TotalBlocks)
	{
		/* PANIC AT THE DISCO ! */
		KERNEL_PANIC("Physical Manager >> OUT OF MEMORY");
	}

	/* Get a frame */
	int64_t Frame = physmem_getframes(Count);

	if(Frame == -1)
	{
		/* PANIC AT THE DISCO ! */
		spinlock_release(PhysMemLock);
		KERNEL_PANIC("Physical Manager >> OUT OF MEMORY");
	}

	/* Mark it used */
	for(i = 0; i < Count; i++)
		MemMap_SetBit(Frame + i);

	/* Release spinlock */
	spinlock_release(PhysMemLock);
    _interrupt_set_state(intr_status);

	/* Calculate Address */
	Addr = (uint64_t)(Frame * PMM_BLOCK_SIZE);
	UsedBlocks++;

	return Addr;
}

void physmem_freeblocks(void *Ptr, uint32_t Size)
{
	/* Calculate frame */
	uint64_t Addr = (uint64_t)Ptr, i;
	int64_t Frame = (int64_t)(Addr / PMM_BLOCK_SIZE);

	/* Get lock */
	interrupt_status_t intr_status = _interrupt_disable();
    spinlock_acquire(PhysMemLock);

    /* Free */
    for(i = 0; i < Size; i++)
    	MemMap_UnsetBit(Frame + i);

    /* Release spinlock */
	spinlock_release(PhysMemLock);
    _interrupt_set_state(intr_status);

    /* Stats */
    UsedBlocks -= Size;
}