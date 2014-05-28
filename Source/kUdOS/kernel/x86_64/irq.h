/*
 * Internal interrupt rutines (arch-specific)
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
 * $Id: irq.h,v 1.9 2003/07/22 19:51:28 ttakanen Exp $
 *
 */

#ifndef KUDOS_KERNEL_INTERRUPT_H
#define KUDOS_KERNEL_INTERRUPT_H

#include "lib/types.h"

/* data types */
typedef uint32_t interrupt_status_t;

typedef struct regs_t
{
	/* General Registers */
	uint64_t rax, rcx, rdx, rbx;
	uint64_t kernel_rsp, rbp, rsi, rdi;
	
	/* Extra registers */
	uint64_t r8, r9, r10, r11;
	uint64_t r12, r13, r14, r15;

	/* Interrupt number & errorcode */
	uint64_t irq, errorcode;

	/* Callee information */
	uint64_t rip, cs, rflags, rsp, ss;

} regs_t;

/* Interrupt type */
typedef void (*int_handler_t)(void);

#define EFLAGS_INTERRUPT_FLAG (1 << 9)

/* Interrupts */
void IsrHandler0(void);
void IsrHandler1(void);
void IsrHandler2(void);
void IsrHandler3(void);
void IsrHandler4(void);
void IsrHandler5(void);
void IsrHandler6(void);
void IsrHandler7(void);
void IsrHandler8(void);
void IsrHandler9(void);
void IsrHandler10(void);
void IsrHandler11(void);
void IsrHandler12(void);
void IsrHandler13(void);
void IsrHandler14(void);
void IsrHandler15(void);
void IsrHandler16(void);
void IsrHandler17(void);
void IsrHandler18(void);
void IsrHandler19(void);

#endif /* KUdos_KERNEL_INTERRUPT_H */
