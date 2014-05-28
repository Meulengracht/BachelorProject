/*
 * Exception Handling
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
 * $Id: exception.h,v 1.0 2003/05/08 12:13:48 philip Exp $
 *
 */

#include <exception.h>
#include <gdt.h>
#include <idt.h>
#include "lib/types.h"
#include "kernel/interrupt.h"

void exception_init() 
{
	//Hardware exceptions x86
	idt_install_gate(0, (uint16_t)(IDT_DESC_PRESENT | IDT_DESC_BIT32), (GDT_KERNEL_CODE << 3), (IrqHandler)IsrHandler0);
	idt_install_gate(1, (uint16_t)(IDT_DESC_PRESENT | IDT_DESC_BIT32), (GDT_KERNEL_CODE << 3), (IrqHandler)IsrHandler1);
	idt_install_gate(2, (uint16_t)(IDT_DESC_PRESENT | IDT_DESC_BIT32), (GDT_KERNEL_CODE << 3), (IrqHandler)IsrHandler2);
	idt_install_gate(3, (uint16_t)(IDT_DESC_PRESENT | IDT_DESC_BIT32), (GDT_KERNEL_CODE << 3), (IrqHandler)IsrHandler3);
	idt_install_gate(4, (uint16_t)(IDT_DESC_PRESENT | IDT_DESC_BIT32), (GDT_KERNEL_CODE << 3), (IrqHandler)IsrHandler4);
	idt_install_gate(5, (uint16_t)(IDT_DESC_PRESENT | IDT_DESC_BIT32), (GDT_KERNEL_CODE << 3), (IrqHandler)IsrHandler5);
	idt_install_gate(6, (uint16_t)(IDT_DESC_PRESENT | IDT_DESC_BIT32), (GDT_KERNEL_CODE << 3), (IrqHandler)IsrHandler6);
	idt_install_gate(7, (uint16_t)(IDT_DESC_PRESENT | IDT_DESC_BIT32), (GDT_KERNEL_CODE << 3), (IrqHandler)IsrHandler7);
	idt_install_gate(8, (uint16_t)(IDT_DESC_PRESENT | IDT_DESC_BIT32), (GDT_KERNEL_CODE << 3), (IrqHandler)IsrHandler8);
	idt_install_gate(9, (uint16_t)(IDT_DESC_PRESENT | IDT_DESC_BIT32), (GDT_KERNEL_CODE << 3), (IrqHandler)IsrHandler9);
	idt_install_gate(10, (uint16_t)(IDT_DESC_PRESENT | IDT_DESC_BIT32), (GDT_KERNEL_CODE << 3), (IrqHandler)IsrHandler10);
	idt_install_gate(11, (uint16_t)(IDT_DESC_PRESENT | IDT_DESC_BIT32), (GDT_KERNEL_CODE << 3), (IrqHandler)IsrHandler11);
	idt_install_gate(12, (uint16_t)(IDT_DESC_PRESENT | IDT_DESC_BIT32), (GDT_KERNEL_CODE << 3), (IrqHandler)IsrHandler12);
	idt_install_gate(13, (uint16_t)(IDT_DESC_PRESENT | IDT_DESC_BIT32), (GDT_KERNEL_CODE << 3), (IrqHandler)IsrHandler13);
	idt_install_gate(14, (uint16_t)(IDT_DESC_PRESENT | IDT_DESC_BIT32), (GDT_KERNEL_CODE << 3), (IrqHandler)IsrHandler14);
	idt_install_gate(15, (uint16_t)(IDT_DESC_PRESENT | IDT_DESC_BIT32), (GDT_KERNEL_CODE << 3), (IrqHandler)IsrHandler15);
	idt_install_gate(16, (uint16_t)(IDT_DESC_PRESENT | IDT_DESC_BIT32), (GDT_KERNEL_CODE << 3), (IrqHandler)IsrHandler16);
	idt_install_gate(17, (uint16_t)(IDT_DESC_PRESENT | IDT_DESC_BIT32), (GDT_KERNEL_CODE << 3), (IrqHandler)IsrHandler17);
	idt_install_gate(18, (uint16_t)(IDT_DESC_PRESENT | IDT_DESC_BIT32), (GDT_KERNEL_CODE << 3), (IrqHandler)IsrHandler18);
	idt_install_gate(19, (uint16_t)(IDT_DESC_PRESENT | IDT_DESC_BIT32), (GDT_KERNEL_CODE << 3), (IrqHandler)IsrHandler19);
}