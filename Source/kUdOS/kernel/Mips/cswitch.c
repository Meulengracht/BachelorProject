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

#include <cswitch.h>
#include "kernel/interrupt.h"

/* Setup new thread context */
void _context_init(context_t *cxt, virtaddr_t entry, 
	virtaddr_t endentry, virtaddr_t stack, uint32_t args)
{
	/* Setup SP and IP */
	cxt->pc = entry;
	cxt->cpu_regs[MIPS_REGISTER_SP] = stack - 4;	/* Reserve space for arg */
	cxt->cpu_regs[MIPS_REGISTER_A0] = args;
	cxt->cpu_regs[MIPS_REGISTER_RA] = endentry;
	cxt->status = INTERRUPT_MASK_ALL | INTERRUPT_MASK_MASTER;
}

void _context_enter_userland(context_t *cxt)
{
	/* Set userland bit and enable interrupts before entering userland. */
    cxt->status = cxt->status | USERLAND_ENABLE_BIT;
    cxt->status = cxt->status | INTERRUPT_MASK_ALL;
    cxt->status = cxt->status | INTERRUPT_MASK_MASTER;
    _cswitch_to_userland(cxt);
}

void _context_set_ip(context_t *cxt, virtaddr_t ip)
{
	/* Set pc */
	cxt->pc = ip;
}

void _context_enable_ints(context_t *cxt)
{
	/* Modify status */
	cxt->status = INTERRUPT_MASK_ALL | INTERRUPT_MASK_MASTER;
}

void _context_set_sp(context_t *cxt, virtaddr_t sp)
{
	cxt->cpu_regs[MIPS_REGISTER_SP] = sp;
}