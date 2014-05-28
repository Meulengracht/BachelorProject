/*
 * The interrupt descriptor table
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
 * $Id: idt.c,v 1.5 2003/03/27 11:38:16 javirta2 Exp $
 *
 */
 
#include <gdt.h>
#include <idt.h>
#include "lib/libc.h"

/* Default Interrupt Handler */
extern void IsrDefaultHandler();

/* IDT */
static idt_desc_t IdtDescriptors[MAX_INTERRUPTS];
static idt_t IdtTable;

void idt_init()
{
	/* Decls */
	int64_t i;

	/* Install Dummy Descriptors */
	for(i = 0; i < MAX_INTERRUPTS; i++)
	{
		idt_install_gate((uint32_t)i, IDT_DESC_PRESENT | IDT_DESC_BIT32,
			(GDT_KERNEL_CODE << 3), (IrqHandler)IsrDefaultHandler);
	}

	/* Setup table */
	IdtTable.Limit = (uint16_t)(sizeof(idt_desc_t) * MAX_INTERRUPTS) - 1;
	IdtTable.Base = (uint64_t)&IdtDescriptors;

	/* Install table */
	asm volatile("lidt (%%rax)" : : "a"((uint64_t)&IdtTable));
}

void idt_install_gate(uint32_t index, uint16_t flags, 
						uint16_t selector, IrqHandler Irq)
{
	/* Sanity */
	if(index > MAX_INTERRUPTS)
		return;

	if(!Irq)
		return;

	/* Get base of interrupt handler */
	uint64_t irqBase = (uint64_t)&(*Irq);

	/* Create IDT Entry */
	IdtDescriptors[index].BaseLow = (uint16_t)(irqBase & 0xFFFF);
	IdtDescriptors[index].BaseMid = (uint16_t)((irqBase >> 16) & 0xFFFF);
	IdtDescriptors[index].BaseHigh = (uint32_t)((irqBase >> 32) & 0xFFFFFFFF);
	IdtDescriptors[index].Reserved0 = 0;
	IdtDescriptors[index].Reserved1 = 0;
	IdtDescriptors[index].Flags = (uint8_t)flags;
	IdtDescriptors[index].Selector = selector;
}