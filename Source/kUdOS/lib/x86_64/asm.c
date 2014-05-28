/*
 * Tools Assembly
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
 * $Id: asm.c,v 1.0 2004/01/13 11:10:50 philip Exp $
 *
 */

#include <asm.h>

/* Send a long */
void _outl(uint16_t Port, uint32_t Value)
{
	asm volatile("outl %%eax, %%dx" : : "d" (Port), "a" (Value));
}

/*uint8_t _inb(uint16_t Port)
{
	uint8_t res = 0;

	asm volatile("inb %%dx, %%al" : "=a"(res) : "d" (Port));

	return res;
}*/

uint16_t _inw(uint16_t Port)
{
	uint16_t res = 0;

	asm volatile("inw %%dx, %%ax" : "=a"(res) : "d" (Port));

	return res;
}

uint32_t _inl(uint16_t Port)
{
	uint32_t res = 0;

	asm volatile("inl %%dx, %%eax" : "=a"(res) : "d" (Port));

	return res;
}

void _insw(uint16_t Port, uint64_t Count, uint8_t *Buffer)
{
	asm volatile("rep;insw" 
		: "=D"(Buffer), "=c"(Count)
		: "D"(Buffer), "c"(Count), "d"((uint64_t)Port)
		: "memory");
}

void _outsw(uint16_t Port, uint64_t Count, uint8_t *Buffer)
{
	asm volatile("rep;outsw" 
		: "=S"(Buffer), "=c"(Count)
		: "S"(Buffer), "c"(Count), "d"((uint64_t)Port)
		: "memory");
}