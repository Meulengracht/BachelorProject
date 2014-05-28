/*
 * Process platform specific code.
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
 * $Id: _proc.c,v 1.11 2007/03/07 18:12:00 ttakanen Exp $
 *
 */
#include <arch.h>
#include "proc/process.h"
#include "proc/elf.h"
#include "kernel/thread.h"
#include "kernel/assert.h"
#include "kernel/interrupt.h"
#include "kernel/config.h"
#include "fs/vfs.h"
#include "vm/memory.h"

void process_map_memory(elf_info_t *elf, openfile_t file, pagetable_t *pagetable)
{
    addr_t phys_page;
    interrupt_status_t intr_status;
    addr_t stack_bottom;
    int i;

    /* Calculate the number of pages needed by the whole process
       (including userland stack). Since we don't have proper tlb
       handling code, all these pages must fit into TLB. */
    KERNEL_ASSERT(elf->ro_pages + elf->rw_pages + CONFIG_USERLAND_STACK_SIZE
		  <= _tlb_get_maxindex() + 1);

    /* Allocate and map stack */
    for(i = 0; i < CONFIG_USERLAND_STACK_SIZE; i++) {
        phys_page = physmem_allocblock();
        KERNEL_ASSERT(phys_page != 0);
        vm_map(pagetable, phys_page, 
               (USERLAND_STACK_TOP & PAGE_SIZE_MASK) - i*PAGE_SIZE, 1);
    }

    /* Allocate and map pages for the segments. We assume that
       segments begin at page boundary. (The linker script in tests
       directory creates this kind of segments) */
    for(i = 0; i < (int)elf->ro_pages; i++) {
        phys_page = physmem_allocblock();
        KERNEL_ASSERT(phys_page != 0);
        vm_map(pagetable, phys_page, 
               elf->ro_vaddr + i*PAGE_SIZE, 1);
    }

    for(i = 0; i < (int)elf->rw_pages; i++) {
        phys_page = physmem_allocblock();
        KERNEL_ASSERT(phys_page != 0);
        vm_map(pagetable, phys_page, 
               elf->rw_vaddr + i*PAGE_SIZE, 1);
    }

    /* Put the mapped pages into TLB. Here we again assume that the
       pages fit into the TLB. After writing proper TLB exception
       handling this call should be skipped. */
    intr_status = _interrupt_disable();
    tlb_fill(pagetable);
    _interrupt_set_state(intr_status);
    
    /* Now we may use the virtual addresses of the segments. */

    /* Zero the pages. */
    memoryset((void *)elf->ro_vaddr, 0, elf->ro_pages*PAGE_SIZE);
    memoryset((void *)elf->rw_vaddr, 0, elf->rw_pages*PAGE_SIZE);

    stack_bottom = (USERLAND_STACK_TOP & PAGE_SIZE_MASK) - 
        (CONFIG_USERLAND_STACK_SIZE-1)*PAGE_SIZE;
    memoryset((void *)stack_bottom, 0, CONFIG_USERLAND_STACK_SIZE*PAGE_SIZE);

    /* Copy segments */

    if (elf->ro_size > 0) {
	/* Make sure that the segment is in proper place. */
        KERNEL_ASSERT(elf->ro_vaddr >= PAGE_SIZE);
        KERNEL_ASSERT(vfs_seek(file, elf->ro_location) == VFS_OK);
        KERNEL_ASSERT(vfs_read(file, (void *)elf->ro_vaddr, elf->ro_size)
		      == (int)elf->ro_size);
    }

    if (elf->rw_size > 0) {
	/* Make sure that the segment is in proper place. */
        KERNEL_ASSERT(elf->rw_vaddr >= PAGE_SIZE);
        KERNEL_ASSERT(vfs_seek(file, elf->rw_location) == VFS_OK);
        KERNEL_ASSERT(vfs_read(file, (void *)elf->rw_vaddr, elf->rw_size)
		      == (int)elf->rw_size);
    }


    /* Set the dirty bit to zero (read-only) on read-only pages. */
    for(i = 0; i < (int)elf->ro_pages; i++) {
        vm_set_dirty(pagetable, elf->ro_vaddr + i*PAGE_SIZE, 0);
    }

    /* Insert page mappings again to TLB to take read-only bits into use */
    intr_status = _interrupt_disable();
    tlb_fill(pagetable);
    _interrupt_set_state(intr_status);
}