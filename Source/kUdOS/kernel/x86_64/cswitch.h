/*
 * Context switch.
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
 * $Id: cswitch.h,v 1.8 2003/05/08 12:13:48 ttakanen Exp $
 *
 */
#ifndef X86_CSWITCH_H
#define X86_CSWITCH_H

#include "lib/types.h"
#include "vm/memory.h"

/* Thread context data structure */
typedef struct {
    uint64_t *stack;   /* The stack */
    uint64_t rip;
    uint64_t flags;
    uint64_t pml4;
    pml4_t *virt_memory;

    void    *prev_context;   /* Previous context in a nested exception chain */
} context_t;

/* Code to be inserted to interrupt vector */
void _cswitch_vector_code(void);

/* Userland entering code */
void _cswitch_to_userland(context_t *usercontext);

/* Context manipulation */
void _context_init(context_t *cxt, virtaddr_t entry, virtaddr_t endentry, 
					virtaddr_t stack, uint32_t args);
void _context_enter_userland(context_t *cxt);
void _context_set_ip(context_t *cxt, virtaddr_t ip); /* Set new instruction pointer / program counter */
void _context_set_sp(context_t *cxt, virtaddr_t sp); /* Sets a new stack pointer */
void _context_enable_ints(context_t *cxt); /* Masks interrupts */

#endif
