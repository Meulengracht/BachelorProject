/*
 * Irq Assembly Rutines
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
 * $Id: irq.s,v 1.5 2003/03/27 11:38:16 philip Exp $
 *
 */
.code64

/* Function Definitions */
.global IsrDefaultHandler
.global _idle_thread_wait_loop
.global _timer_set_ticks
.global yield_irq_handler
.global __enable_irq
.global __disable_irq
.global __getflags
.global IsrHandler0
.global IsrHandler1
.global IsrHandler2
.global IsrHandler3
.global IsrHandler4
.global IsrHandler5
.global IsrHandler6
.global IsrHandler7
.global IsrHandler8
.global IsrHandler9
.global IsrHandler10
.global IsrHandler11
.global IsrHandler12
.global IsrHandler13
.global IsrHandler14
.global IsrHandler15
.global IsrHandler16
.global IsrHandler17
.global IsrHandler18
.global IsrHandler19

/* Software Interrupts */
.global _interrupt_yield

IsrDefaultHandler:
	iretq

_interrupt_yield:
	int $0x81
	ret

_idle_thread_wait_loop:
	hlt
	jmp _idle_thread_wait_loop

_timer_set_ticks:
	ret

__enable_irq:
	sti
	ret

__disable_irq:
	cli
	ret

__getflags:
	pushfq
	pop %rax
	ret

/* IRQ Macros */
.macro PUSHAQ
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
.endm

.macro POPAQ
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
.endm

/* Yield */
.extern pic_eoi
.extern task_switch

yield_irq_handler:
	 /* Disable interrupts */
	cli

	/* Save registers */
	PUSHAQ

	/* Switch task */
	mov %rsp, %rdi
	call task_switch

	/* It returns a new stack for us in rax */
	mov %rax, %rsp

	/* Acknowledge irq */
	mov $0, %rdi
	call pic_eoi

	/* Restore */
	POPAQ

	/* Reenable interrupts */
	sti

	/* Return */
	iretq

/* Common Entry */
.extern interrupt_handle
.global IsrCommon

IsrCommon:
	/* Disable interrupts */
	cli

	/* Save registers */
	PUSHAQ
	
	/* Mov info */
	mov %rsp, %rdi

	/* Call common entry */
	call interrupt_handle

	/* Restore */
	POPAQ

	/* Reenable interrupts */
	sti

	/* Return */
	add $16, %rsp
	iretq

/* IRQS */
IsrHandler0:
	pushq 0
	pushq 0
	jmp IsrCommon

IsrHandler1:
	pushq 0
	pushq 1
	jmp IsrCommon

IsrHandler2:
	pushq 0
	pushq 2
	jmp IsrCommon

IsrHandler3:
	pushq 0
	pushq 3
	jmp IsrCommon

IsrHandler4:
	pushq 0
	pushq 4
	jmp IsrCommon

IsrHandler5:
	pushq 0
	pushq 5
	jmp IsrCommon

IsrHandler6:
	pushq 0
	pushq 6
	jmp IsrCommon

IsrHandler7:
	pushq 0
	pushq 7
	jmp IsrCommon

IsrHandler8:
	pushq 8
	jmp IsrCommon

IsrHandler9:
	pushq 0
	pushq 9
	jmp IsrCommon

IsrHandler10:
	pushq 10
	jmp IsrCommon

IsrHandler11:
	pushq 11
	jmp IsrCommon

IsrHandler12:
	pushq 12
	jmp IsrCommon

IsrHandler13:
	pushq 13
	jmp IsrCommon

IsrHandler14:
	hlt
	pushq 14
	jmp IsrCommon

IsrHandler15:
	pushq 0
	pushq 15
	jmp IsrCommon

IsrHandler16:
	pushq 0
	pushq 16
	jmp IsrCommon

IsrHandler17:
	pushq 17
	jmp IsrCommon

IsrHandler18:
	pushq 0
	pushq 18
	jmp IsrCommon

IsrHandler19:
	pushq 0
	pushq 19
	jmp IsrCommon