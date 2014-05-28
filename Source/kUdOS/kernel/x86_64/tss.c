/*
 * The task switch segment descriptor.
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
 * $Id: tss.h,v 1.0 2003/07/22 19:51:28 philip Exp $
 *
 */

#include <gdt.h>
#include <tss.h>
#include "kernel/config.h"
#include "lib/libc.h"

tss_t tss_descriptors[CONFIG_MAX_CPUS];

/* Helpers */
void tss_flush(uint16_t tss)
{
	asm volatile("ltr %%ax" : : "a"(tss));
}

/* Init */
void tss_init(void)
{
	/* Null out entries */
	memoryset(&tss_descriptors[0], 0, sizeof(tss_t) * CONFIG_MAX_CPUS);
}

/* Sets up TSS descriptors for each cpu */
void tss_install(int num_cpu, uint64_t cpu_stack)
{
	/* Null out TSS */
	uint64_t tss_base = (uint64_t)&tss_descriptors[num_cpu];
	memoryset((uint64_t*)tss_base, 0, sizeof(tss_t));

	/* Install it */
	gdt_install_tss(tss_base, sizeof(tss_t));

	/* Set stack */
	tss_descriptors[num_cpu].rsp_ring0 = cpu_stack;
	tss_descriptors[num_cpu].io_map = 0xFFFF;
	tss_descriptors[num_cpu].ist[0] = cpu_stack;

	/* Update hardware task register */
	tss_flush((uint16_t)((5 + num_cpu) * sizeof(gdt_desc_t)));
}

/* Update stacks */
void tss_setstack(uint32_t cpu, uint64_t stack)
{
	tss_descriptors[cpu].rsp_ring0 = stack;
}

void tss_setuserstack(uint32_t cpu, uint64_t stack)
{
	tss_descriptors[cpu].rsp_ring2 = stack;
}
