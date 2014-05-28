/*
 * Polling TTY driver.
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
 * $Id: polltty.c,v 1.13 2003/04/03 15:22:46 tlilja Exp $
 *
 */

#include <tty.h>
#include <keyboard.h>
#include "lib/types.h"
#include "drivers/device.h"
#include "drivers/drivers.h"
#include "drivers/gcd.h"

/** @name Polling TTY driver
 * 
 * This module implements the polling TTY driver. The polling TTY
 * driver is used to print kernel messages and to get input from the
 * user to the kernel. Since the driver is a polling driver, the I/O
 * will be performed before advancing in the code.
 *
 * @{
 */
extern device_t *tty_init(io_descriptor_t *desc);


/** 
 * The io base area for the polling TTY. This is initialized in the
 * initialization function of the polling TTY driver. After that it
 * can be used when outputting or inputting characters. If no TTY is
 * found, the value of this variable is zero.
 */
tty_t *polltty_iobase;
gcd_t *polltty_gcd;
device_t *tty_dev;

/**
 * Initializes the polling TTY driver. Goes through the IO descriptors
 * provided by YAMS searching for the first TTY. Sets
 * \texttt{polltty\_iobase} to point to the io base area of the
 * polling TTY. If no TTY is found sets \texttt{polltty\_iobase} to
 * zero.
 */
void polltty_init() 
{
	/* For obvious reasons, and contrary to the mips initialization
     * we need to initialise tty aswell here */
	tty_dev = tty_init(0);

    /* Get IO base */
    polltty_iobase = (tty_t*)tty_dev->real_device;
    polltty_gcd = (gcd_t*)tty_dev->generic_device;
}

/**
 * Gets one character from the TTY.
 *
 * @return The character read from the TTY. If the
 * \texttt{polltty_iobase} is invalid, returns 0.
 *
 */
int polltty_getchar() 
{
    /* Need keyboard driver */
    return (int)keyboard_getkey();
}

/**
 * Outputs one character to the TTY. If the \texttt{polltty_iobase} is
 * invalid nothing is done.
 *
 * @param c The character to be output to the TTY.
 *
 */
void polltty_putchar(int c)
{
	uint64_t CharPtr = c;
    polltty_gcd->write(polltty_gcd, (const void*)CharPtr, 1);
}

/** @} */
