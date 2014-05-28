/*
 * The global descriptor table.
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
 * $Id: gdt.h,v 1.0 2003/07/22 19:51:28 philip Exp $
 *
 */

#ifndef __GDT_H__
#define __GDT_H__

/* Includes */
#include "lib/types.h"

/* Defines */
#define GDT_DESC_ACCESS			0x1	/* Access Bit */
#define GDT_DESC_READWRITE		0x2	/* If set, we have read/write priveligies */
#define GDT_DESC_EXPANSION		0x4	/* Direction of expansion */
#define GDT_DESC_EXECUTABLE		0x8	/* Descriptor TYPE */
#define GDT_DESC_CODEDATA		0x10	/* Is this a code or data descriptor ? */
#define GDT_DESC_DPL			0x60	/* Priveligie Level (0 - Kernel) */
#define GDT_DESC_MEMORY			0x80	/* Set present bit */

#define GDT_GRAN_LIMITHI_MASK		0x0F	/* Masks out high-limit */
#define GDT_GRAN_OS			0x10	/* Set OS defined bit */
#define GDT_GRAN_64BIT			0x20	/* Set if 64 bit */
#define GDT_GRAN_32BIT			0x40	/* Set if 32 bit, else its 16 bit */
#define GDT_GRAN_4K			0x80	/* Set for 4K Grandularity, default is none */

/* GDT Descriptor Entries */
#define GDT_KERNEL_CODE			0x1
#define GDT_KERNEL_DATA			0x2
#define GDT_USER_CODE			0x3
#define GDT_USER_DATA			0x4


/* Structures */
#define MAX_DESCRIPTORS			16

/* GDT Descriptor */
typedef struct GdtDescriptor
{
	/* Bits 0-15 of segment limit */
	uint16_t Limit;

	/* Bits 0-23 of base address */
	uint16_t BaseLow;

	/* ^ 16 - 23 */
	uint8_t BaseMid;

	/* Descriptor Access Flags */
	uint8_t Flags;

	/* Grandularity */
	uint8_t Grandularity;

	/* 23-31 of base address */
	uint8_t BaseHigh;

} __attribute__((packed)) gdt_desc_t;

typedef struct GDTSystemDescriptor
{
	/* Limit 1 */
	uint16_t Limit0;
	uint16_t Addr0;

	uint8_t Addr1;
	uint8_t Type0;

	/* Low 4 bits - Limit, High 4 bits - Type1 */
	uint8_t Limit1;
	uint8_t Addr2;

	uint32_t Addr3;
	uint32_t Reserved;

} __attribute__((packed)) gdt_sys_desc_t;

/* Global Descriptor Table */
typedef struct GdTable
{
	/* Size of GDT */
	uint16_t Limit;

	/* Base Address of GDT */
	uint64_t Base;

} __attribute__((packed)) gdt_t;

/* Prototypes */
void gdt_init();

void gdt_install_tss(uint64_t base, uint64_t limit);
void gdt_install_descriptor(uint64_t base, uint64_t limit,
				uint8_t access, uint8_t grandularity);


#endif



