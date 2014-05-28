/*
 * Main startup routines for KUdos
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
 * $Id: main.c,v 1.25 2006/01/13 05:44:34 jaatroko Exp $
 *
 */

#include <multiboot.h>
#include "init/common.h"
#include "kernel/interrupt.h"
#include "vm/memory.h"
#include "lib/types.h"
#include "lib/libc.h"
#include "drivers/polltty.h"
#include "kernel/stalloc.h"
#include "kernel/thread.h"
#include "kernel/sleepq.h"
#include "kernel/semaphore.h"
#include "kernel/scheduler.h"
#include "drivers/device.h"
#include "drivers/bootargs.h"
#include "fs/vfs.h"
#include <keyboard.h>

/**
 * Initialize the system. This function is called by CPU0 just
 * after the kernel code is entered first time after boot.
 *
 * The system is still in bootup-mode and can't run threads or multiple
 * CPUs.
 *
 */

int init(uint64_t Magic, uint8_t *Multiboot)
{
	/* Setup Static Allocation System */
	multiboot_info_t *MbInfo = (multiboot_info_t*)Multiboot;
    TID_t startup_thread;
    stalloc_init();

    /* Setup video printing */
    polltty_init();

    kprintf("KUdos is the operating system of University of Copenhagen\n");
    kprintf("==========================================================\n");
    kprintf("\n");

    kprintf("Copyright (C) 2003-2014  Juha Aatrokoski, Timo Lilja,\n");
    kprintf("  Leena Salmela, Teemu Takanen, Aleksi Virtanen, Philip Meulengracht.\n");
    kprintf("See the file COPYING for licensing details.\n");
    kprintf("\n");

    /* Setup GDT/IDT/Exceptions */
    kprintf("Initializing interrupt handling\n");
    interrupt_init(1);

    /* Read boot args */
    kprintf("Reading boot arguments\n");
    bootargs_init((void*)(uint64_t)MbInfo->CmdLine);

    /* Setup Memory */
    kprintf("Initializing memory system\n");
    physmem_init(Multiboot);
    vm_init();
    heap_init();

    /* Seed the random number generator. */
    if (bootargs_get("randomseed") == NULL) {
	_set_rand_seed(0);
    } else {
	int seed = atoi((char*)(uint64_t)bootargs_get("randomseed"));
	kprintf("Seeding pseudorandom number generator with %i\n", seed);
	_set_rand_seed(seed);
    }

    /* Setup Threading */
    kprintf("Initializing threading table\n");
    thread_table_init();

    kprintf("Initializing sleep queue\n");
    sleepq_init();

    kprintf("Initializing semaphores\n");
    semaphore_init();

    /* Start scheduler */
    kprintf("Initializing scheduler\n");
    scheduler_init();

    /* Setup Drivers */
    kprintf("Initializing device drivers\n");
    device_init();

    kprintf("Initializing virtual filesystem\n");
    vfs_init();

    kprintf("Creating initialization thread\n");
    startup_thread = thread_create(init_startup_thread, 0);
    thread_run(startup_thread);

    kprintf("Starting threading system and SMP\n");

    /* Enter context switch, scheduler will be run automatically,
       since thread_switch() behaviour is identical to timer tick
       (thread timeslice is over). */
    thread_switch();
    
    return 0xDEADBEEF;
}
