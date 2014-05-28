/*
 * Timer handling
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
 * $Id: _timer.S,v 1.3 2005/08/28 18:17:22 jaatroko Exp $
 *
 */
.code64

/* IRQ Timer (PIT) */
.global pit_irq_handler

.extern pit_counter
.extern pic_eoi
.extern task_switch

pit_irq_handler:
	 /* Disable interrupts */
	cli

	/* Save registers */
	mov %r15, -0x8(%rsp)
	mov %r14, -0x10(%rsp)
	mov %r13, -0x18(%rsp)
	mov %r12, -0x20(%rsp)
	mov %r11, -0x28(%rsp)
	mov %r10, -0x30(%rsp)
	mov %r9,  -0x38(%rsp)
	mov %r8,  -0x40(%rsp)
	mov %rdi, -0x48(%rsp)
	mov %rsi, -0x50(%rsp)
	mov %rbp, -0x58(%rsp)
	mov %rsp, -0x60(%rsp)
	mov %rbx, -0x68(%rsp)
	mov %rdx, -0x70(%rsp)
	mov %rcx, -0x78(%rsp)
	mov %rax, -0x80(%rsp)
	sub $0x80, %rsp

	/* Do stuff! */
	xor %rax, %rax
	mov $pit_counter, %eax
	add $0x1, (%rax)

	/* Switch task */
	mov %rsp, %rdi
	call task_switch

	/* It returns a new stack for us in rax */
	mov %rax, %rsp

	/* Acknowledge irq */
	mov $0, %rdi
	call pic_eoi

	/* Restore */
	add $0x80, %rsp
	mov -0x8(%rsp), %r15
	mov -0x10(%rsp), %r14
	mov -0x18(%rsp), %r13
	mov -0x20(%rsp), %r12
	mov -0x28(%rsp), %r11
	mov -0x30(%rsp), %r10
	mov -0x38(%rsp), %r9
	mov -0x40(%rsp), %r8
	mov -0x48(%rsp), %rdi
	mov -0x50(%rsp), %rsi
	mov -0x58(%rsp), %rbp
	mov -0x68(%rsp), %rbx
	mov -0x70(%rsp), %rdx
	mov -0x78(%rsp), %rcx
	mov -0x80(%rsp), %rax

	/* Reenable interrupts */
	sti

	/* Return */
	iretq