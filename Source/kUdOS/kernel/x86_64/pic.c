/*
 * The programmable interrupt controller.
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
 * $Id: pic.h,v 1.0 2003/07/22 19:51:28 philip Exp $
 *
 */

#include <pic.h>
#include <asm.h>
#include "kernel/interrupt.h"
#include "lib/libc.h"

void pic_sendcommand(uint8_t Pic, uint8_t Command)
{
	/* Sanity */
 	if(Pic > 1)
 		return;

 	/* Get register */
 	uint16_t Reg = (Pic == SECONDARY_PIC) ? (uint16_t)PIC1_COMMAND_REGISTER : 
 											(uint16_t)PIC0_COMMAND_REGISTER;

 	/* Send byte */
 	_outb(Reg, Command);
}

void pic_senddata(uint8_t Pic, uint8_t Data)
{
	/* Sanity */
 	if(Pic > 1)
 		return;

 	/* Get register */
 	uint16_t Reg = (Pic == SECONDARY_PIC) ? (uint16_t)PIC1_INT_MASK_REGISTER : 
 											(uint16_t)PIC0_INT_MASK_REGISTER;

 	/* Send byte */
 	_outb(Reg, Data);
}

uint8_t pic_getdata(uint8_t Pic)
{
	/* Sanity */
 	if(Pic > 1)
 		return 0;

 	/* Get register */
 	uint16_t Reg = (Pic == SECONDARY_PIC) ? (uint16_t)PIC1_INT_MASK_REGISTER : 
 											(uint16_t)PIC0_INT_MASK_REGISTER;

 	/* Get byte */
 	return _inb(Reg);
}

void pic_init()
{
	/* Control Word */
	uint8_t icw = 0;

	/* Setup initialization control word 1 */
	icw |= PIC_ICW1_MASK_INIT | PIC_ICW1_MASK_IC4;

	/* Send to both master and slave to start them */
	pic_sendcommand(PRIMARY_PIC, icw);	//11
	pic_sendcommand(SECONDARY_PIC, icw);

	/* Remap PICS */
	pic_senddata(PRIMARY_PIC, 0x20); /* Pic 0 start at 0x20 */
	pic_senddata(SECONDARY_PIC, 0x28); /* Pic 1 start at 0x28 */

	/* Send initialization control word 3 
	 * this is to establish the connection between master 
	 * and slave controllers (we set primary as master, and secondary as slave) */
	pic_senddata(PRIMARY_PIC, 0x04);
	pic_senddata(SECONDARY_PIC, 0x02);

	/* Last step is to send initialization control word 4 */
	/* We tell controller to enable i86 mode */
	icw = PIC_ICW4_MASK_UPM;

	pic_senddata(PRIMARY_PIC, icw);
	pic_senddata(SECONDARY_PIC, icw);

	/* Activate IRQs */
	pic_senddata(PRIMARY_PIC, 0);
	pic_senddata(SECONDARY_PIC, 0);

	/* enable interrupts */
	_interrupt_enable();

	/* Kickstart things */
	pic_eoi(8);
}

void pic_maskinterrupt(uint8_t irq)
{
	uint16_t Port;
	uint8_t Value;

	/* Which Pic ? */
	if(irq < 8)
		Port = PIC0_INT_MASK_REGISTER;
	else
	{
		Port = PIC1_INT_MASK_REGISTER;
		irq -= 8;
	}

	/* Get current int status and set irq to disabled */
	Value = _inb(Port) | (1 << irq);

	/* Send new status */
	_outb(Port, Value);
}

void pic_unmaskinterrupt(uint8_t irq)
{
	uint16_t Port;
	uint8_t Value;

	/* Which Pic ? */
	if(irq < 8)
		Port = PIC0_INT_MASK_REGISTER;
	else
	{
		Port = PIC1_INT_MASK_REGISTER;
		irq -= 8;
	}

	/* Get current int status and set irq to enabled */
	Value = _inb(Port) & ~(1 << irq);

	/* Send new status */
	_outb(Port, Value);
}

void pic_eoi(uint8_t irq)
{
	/* Acknowledge IRQ */
	if(irq >= 8)
		_outb(PIC1_COMMAND_REGISTER, 0x20);

	_outb(PIC0_COMMAND_REGISTER, 0x20);
}