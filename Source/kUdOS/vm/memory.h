/*
 * Memory Management.
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
 * $Id: memory.h,v 1.0 2014/05/08 13:47:19 philip Exp $
 *
 */

#ifndef __KUDOS_MEMORY_H__
#define __KUDOS_MEMORY_H__

/* Includes */
#include "lib/types.h"
#include <mem.h>
#include <pagetable.h>

/* Physical Memory Management */
/* For the architecture that supports it */

/* Prototypes */
void physmem_init(void *BootInfo);

physaddr_t physmem_allocblock();
physaddr_t physmem_allocblocks(uint32_t Count);

void physmem_freeblock(void *Ptr);
void physmem_freeblocks(void *Ptr, uint32_t Size);

/* Virtual Memory Management */
#define USERLAND_STACK_TOP 0x7fffeffc

/* For the architecture that supports it */
void vm_init(void);

void vm_map(pagetable_t *pagetable, physaddr_t physaddr, 
	    virtaddr_t vaddr, int flags);
void vm_unmap(pagetable_t *pagetable, virtaddr_t vaddr);

physaddr_t vm_getmap(pagetable_t *pagetable, virtaddr_t vaddr);
void vm_set_dirty(pagetable_t *pagetable, virtaddr_t vaddr, int dirty);

pagetable_t *vm_create_pagetable(uint32_t asid);
void vm_destroy_pagetable(pagetable_t *pagetable);
void vm_update_mappings(virtaddr_t *thread);


/* Kernel Heap Memory Management 
 * Provides dynamic memory allocation */

/* Heap Structure - Linked List */
typedef struct heap_header_t
{
	/* Address */
	virtaddr_t addr;

	/* Flags */
	uint32_t flags;

	/* Length of this block */
	uint32_t length;

	/* Next link */
	struct heap_header_t *link;

} heap_header_t;

/* Defines */
#define MM_HEAP_LOCATION	0x10000000
#define MM_HEAP_ADDR_OFFSET	0x200000
#define MM_HEAP_SIZE		(0x20000000 - (MM_HEAP_LOCATION + MM_HEAP_ADDR_OFFSET))
#define MM_HEAP_END		0x20000000

#define MM_HEAP_FLAG_ALLOCATED	0x1

void heap_init(void);
virtaddr_t *kmalloc(uint32_t length);
void kfree(void *ptr);

#endif
