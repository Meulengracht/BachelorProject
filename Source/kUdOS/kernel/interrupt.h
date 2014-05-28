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
 * $Id: interrupt.h,v 2.0 2003/07/22 19:51:28 ttakanen Exp $
 *
 */

#ifndef KUDOS_INTERRUPT_H
#define KUDOS_INTERRUPT_H

#include "lib/types.h"
#include "drivers/device.h"
#include <irq.h>
#include "vm/memory.h"

/* structure for registered interrupt handlers */
typedef struct {
    device_t *device;
    uint32_t irq;
    int_handler_t handler;
} interrupt_entry_t;

/* C functions */

void interrupt_init(int num_cpus);
void interrupt_register(uint32_t irq, int_handler_t handler, device_t *device);
void interrupt_handle(virtaddr_t cause);

/* assembler functions */
interrupt_status_t _interrupt_disable(void);
interrupt_status_t _interrupt_enable(void);
interrupt_status_t _interrupt_set_state(interrupt_status_t);
interrupt_status_t _interrupt_get_state(void);
interrupt_status_t _interrupt_is_disabled(void);

/* Arch Specific */
void _interrupt_yield(void);
int _interrupt_getcpu(void);

#endif /* KUdos_KERNEL_INTERRUPT_H */
