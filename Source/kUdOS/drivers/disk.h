/*
 * Disk driver
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
 * $Id: disk.h,v 1.4 2003/05/02 08:02:44 javirta2 Exp $
 *
 */

#ifndef DRIVERS_DISK_H
#define DRIVERS_DISK_H

#include <arch.h>
#include <_disk.h>
#include "lib/libc.h"
#include "kernel/spinlock.h"
#include "kernel/semaphore.h"
#include "drivers/device.h"
#include "drivers/gbd.h"

/* Internal data structure for disk driver. */
typedef struct {
    /* spinlock for synchronization of access to this data structure. */
    spinlock_t                 slock;

    /* Queue of pending requests. New requests are placed to queue
       by disk scheduling policy (see disksched_schedule()). */
    volatile gbd_request_t     *request_queue;    

    /* Request currently served by the driver. If NULL device is idle. */
    volatile gbd_request_t     *request_served;
} disk_real_device_t;


/* functions */
device_t *disk_init(io_descriptor_t *desc);


#endif /* DRIVERS_DISK_H */

