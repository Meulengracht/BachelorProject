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
 * $Id: _disk.h,v 1.4 2003/05/02 08:02:44 javirta2 Exp $
 *
 */

#ifndef DRIVERS_INTTERNAL_DISK_H
#define DRIVERS_INTTERNAL_DISK_H

/* Includes */

/* Defines */
#define IDE_CHANNELS_PER_CTRL	0x2	/* 2 Channels per Controller */
#define IDE_DEVICES_PER_CHANNEL	0x2	/* 2 Devices per Channel (slaver & master) */

/* Default Ports */
#define IDE_PRIMARY_CMD_BASE	0x1F0
#define IDE_PRIMARY_CTRL_BASE	0x3F6
#define IDE_PRIMARY_IRQ		14

#define IDE_SECONDARY_CMD_BASE	0x170
#define IDE_SECONDARY_CTRL_BASE	0x376
#define IDE_SECONDARY_IRQ	15

#define IDE_PRIMARY		0
#define IDE_SECONDARY		1

#define IDE_REGISTER_DATA	0x00
#define IDE_REGISTER_FEATURES	0x01
#define IDE_REGISTER_SECCOUNT0	0x02
#define IDE_REGISTER_LBA0	0x03
#define IDE_REGISTER_LBA1	0x04
#define IDE_REGISTER_LBA2	0x05
#define IDE_REGISTER_HDDSEL	0x06
#define IDE_REGISTER_COMMAND	0x07
#define IDE_REGISTER_STATUS	0x07
#define IDE_REGISTER_CTRL	0x0C

#define IDE_COMMAND_PIO_READ	0x20
#define IDE_COMMAND_PIO_WRITE	0x30
#define IDE_COMMAND_PACKET	0xA1
#define IDE_COMMAND_FLUSH	0xE7
#define IDE_COMMAND_IDENTIFY	0xEC

#define IDE_ERROR_GENERIC	0x01
#define IDE_ERROR_DRQ		0x08
#define IDE_ERROR_FAULT		0x20

#define IDE_ATA_BUSY		0x80
#define IDE_ATA_DRQ		0x08

#define IDE_READ		0x00
#define IDE_WRITE		0x01

/* Structures */

/* IDE Channel */
typedef struct ide_channel_t
{
	/* I/O Base */
	uint16_t base;
	
	/* Control Base */
	uint16_t ctrl;

	/* Bus Master Base */
	uint16_t busm;

	/* Irq Number */
	uint8_t irq;

	/* Interrupt or Polling? */
	uint32_t use_irq;
	uint32_t use_dma;
	
	/* Irq waiting? */
	volatile uint32_t irq_wait;

	/* Dma Buffers */
	uint32_t dma_phys;
	uint32_t dma_virt;
	uint32_t dma_buf_phys;
	uint32_t dma_buf_virt;
	
} ide_channel_t;

/* Ide Device */
typedef struct ide_device_t
{
	/* Driver Present? */
	uint8_t present;
	uint8_t channel;	/* 0 - primary, 1 - secondary */
	uint8_t drive;		/* 0 - master, 1 - slave */

	uint8_t flags; 		/* 1 - LBA48, 2 - DMA */

	uint16_t type;		/* 0 - ATA, 1 - ATAPI */ 
	uint16_t signature;	/* Drive Signature */

	uint16_t capabilities;	/* Features */
	uint32_t commandset;	/* Command set supported */

	uint16_t cylinders;
	uint16_t headspercylinder;
	uint64_t secsperhead;
	uint64_t totalsectors;

} ide_device_t;

#endif /* DRIVERS_DISK_H */
