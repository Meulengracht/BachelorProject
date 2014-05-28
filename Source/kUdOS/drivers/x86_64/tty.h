/*
 * TTY driver for x86
 *
 * Copyright (C) 2014 Juha Aatrokoski, Timo Lilja,
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
 * $Id: tty.h,v 1.0 2014/04/28 20:56:06 Philip Exp $
 *
 */

#ifndef TTY_H
#define TTY_H

#include <arch.h>
#include "kernel/spinlock.h"

/* x86 TTY definitions */
#define VIDEO_MEMORY_BASE       0xB8000
#define VIDEO_MEMORY_COLUMNS    80
#define VIDEO_MEMORY_ROWS       25

/* Text Colors */
#define COLOR_BLACK		0x00
#define COLOR_BLUE		0x01
#define COLOR_GREEN		0x02
#define COLOR_CYAN		0x03
#define COLOR_RED		0x04
#define COLOR_MAGENTA		0x05
#define COLOR_BROWN		0x06
#define COLOR_LGRAY		0x07
#define	COLOR_DGRAY		0x08
#define COLOR_LBLUE		0x09
#define COLOR_LGREEN		0x0A
#define COLOR_LCYAN		0x0B
#define COLOR_LRED		0x0C
#define COLOR_LMAGENTA		0x0D
#define COLOR_YELLOW		0x0E
#define COLOR_WHITE		0x0F

/* The structure of a "terminal" */
typedef struct {
    uint64_t CursorX;    /* Text position X */
    uint64_t CursorY;     /* Text position Y */
    uint64_t TextColor;    /* Text color */
    spinlock_t *slock;    /* Synchronization */
} tty_t;

#endif /* TTY_H */
