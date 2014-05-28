/*
 * The global descriptor table
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
 * $Id: gdt.c,v 1.5 2003/03/27 11:38:16 javirta2 Exp $
 *
 */
 
#include <gdt.h>
#include "lib/libc.h"

/* GDT */
static gdt_desc_t gdtdescriptors[MAX_DESCRIPTORS];
static gdt_t gdt;
static uint32_t gdt_index;

void gdt_init()
{
	/* null out the gdt & descriptors */
	gdt_index = 0;
	memoryset(&gdt, 0, sizeof(gdt_t));
	memoryset(&gdtdescriptors, 0, sizeof(gdt_desc_t) * MAX_DESCRIPTORS);

	/* Setup table */
	gdt.Limit = (sizeof(gdt_desc_t) * MAX_DESCRIPTORS) - 1;
	gdt.Base = (uint64_t)&gdtdescriptors[0];

	/* Install Descriptors */

	/* Null descriptor, all GDT starts with null descriptors */
	gdt_install_descriptor(0, 0, 0, 0);

	/* Kernel Code Descriptor, 0x08 */
	gdt_install_descriptor(0, 0, 
		GDT_DESC_MEMORY | GDT_DESC_READWRITE | 
		GDT_DESC_EXECUTABLE | GDT_DESC_CODEDATA,
		GDT_GRAN_4K | GDT_GRAN_64BIT);

	/* Kernel Data Descriptor, 0x10 */
	gdt_install_descriptor(0, 0, 
		GDT_DESC_MEMORY | GDT_DESC_READWRITE | 
		GDT_DESC_CODEDATA, GDT_GRAN_4K | GDT_GRAN_64BIT);

	/* User Code Descriptor, 0x18 */
	gdt_install_descriptor(0, 0, 
		GDT_DESC_MEMORY | GDT_DESC_READWRITE | 
		GDT_DESC_EXECUTABLE | GDT_DESC_CODEDATA | GDT_DESC_DPL,
		GDT_GRAN_4K | GDT_GRAN_64BIT);

	/* User Data Descriptor, 0x20 */
	gdt_install_descriptor(0, 0, 
		GDT_DESC_MEMORY | GDT_DESC_READWRITE | 
		GDT_DESC_CODEDATA | GDT_DESC_DPL, 
		GDT_GRAN_4K | GDT_GRAN_64BIT);

	/* Install table */
	asm volatile("lgdt (%%rax)" : : "a"((uint64_t)&gdt));
}

void gdt_install_descriptor(uint64_t base, uint64_t limit,
				uint8_t access, uint8_t grandularity)
{
	/* Sanity */
	if(gdt_index > MAX_DESCRIPTORS)
		return;

	/* Setup */
	gdtdescriptors[gdt_index].BaseLow = (uint16_t)(base & 0xFFFF);
	gdtdescriptors[gdt_index].BaseMid = (uint8_t)((base >> 16) & 0xFF);
	gdtdescriptors[gdt_index].BaseHigh = (uint8_t)((base >> 24) & 0xFF);
	gdtdescriptors[gdt_index].Limit = (uint16_t)(limit & 0xFFFF);

	gdtdescriptors[gdt_index].Flags = access;
	gdtdescriptors[gdt_index].Grandularity = (uint8_t)((limit >> 16) & 0x0F);
	gdtdescriptors[gdt_index].Grandularity |= grandularity & 0xF0;

	gdt_index++;
}

void gdt_install_tss(uint64_t base, uint64_t limit)
{
	/* Setup */
	uint16_t tss_type = 0x0089;
	gdt_sys_desc_t *gdt_desc = (gdt_sys_desc_t*)&gdtdescriptors[gdt_index];

	/* Sanity */
	if(gdt_index > MAX_DESCRIPTORS)
		return;

	gdt_desc->Type0 = (uint16_t)(tss_type & 0x00FF);
	gdt_desc->Limit1 = (uint8_t)((tss_type & 0xF000) >> 12);

	gdt_desc->Addr0 = base & 0xFFFF;
	gdt_desc->Addr1 = (base & 0xFF0000) >> 16;
	gdt_desc->Addr2 = (base & 0xFF000000) >> 24;
	gdt_desc->Addr3 = base >> 32;

	gdt_desc->Limit0 = limit & 0xFFFF;
	gdt_desc->Limit1 = (limit & 0xF0000) >> 16;

	gdt_desc->Reserved = 0;

	gdt_index += 2;
}