/*
 * Metadevices (RTC)
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
 * $Id: metadev.c,v 1.6 2005/03/08 12:57:34 lsalmela Exp $
 *
 */
#include <pit.h>
#include "drivers/metadev.h"
#include "lib/libc.h"
#include "kernel/panic.h"
#include "kernel/assert.h"
#include "kernel/stalloc.h"
#include "kernel/interrupt.h"

/**@name Metadevices
 *
 * This module implements drivers for so called metadevices. These are
 * devices documented in YAMS specification as non-peripheral devices.
 * Metadevices include RTC (Real Time Clock), MemInfo (Memory
 * Information) and shutdown device.
 * They are not really used for X86 and we thus only implement
 * the bare minimum for dual-architecture compatability
 * @{
 */

/** Get number of timer ticks elapsed since system startup from the
 * system RTC. Returns the number of timer ticks since system startup
 *
 * @return Number of timer ticks elapsed
 */
uint32_t rtc_get_msec()
{
    return get_clock(); /* MSEC @0x00 */
}
