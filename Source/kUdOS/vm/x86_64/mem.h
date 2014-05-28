/*
 * Internal Memory Configuration
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
 * $Id: mem.h,v 1.0 2014/05/08 13:47:19 philip Exp $
 *
 */

#ifndef __MEM_H__
#define __MEM_H__

#include "lib/types.h"
#include <pagetable.h>

/* In this header we need to define the 
 * two sizes of virtual and physical addresses */
typedef uint64_t physaddr_t;
typedef uint64_t virtaddr_t;
typedef uint64_t addr_t;
typedef int64_t saddr_t;

/* Dummy defines */
#define ADDR_KERNEL_TO_PHYS(x) x
#define ADDR_PHYS_TO_KERNEL(x) x

/* Multiboot Memory Map Structure */
enum MemMapTypes
{
	MemType_Free = 1,	/* This is for us */
	MemType_Reserved,	/* Memory we cannot use */
	MemType_Reclaim,	/* This is the ACPI memory space */
	MemType_NVRAM		/* ACPI NVS Memory - Let it be */
};

typedef struct MemoryRegion
{
	uint32_t Size;
	uint64_t BaseAddress;
	uint64_t Length;
	uint32_t Type;
} __attribute__((packed)) mem_region_t;

void vmm_setcr3(uint64_t pdbr);
uint64_t vmm_get_kernel_pml4();
pml4_t *vmm_get_kernel_vmem();

#endif
















