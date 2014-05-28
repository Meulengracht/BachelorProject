/*
 * Multiboot Structure .
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
 * $Id: multiboot.h,v 1.0 2014/05/08 13:47:19 philip Exp $
 *
 */

#ifndef __KUDOS_MULTIBOOT_H__
#define __KUDOS_MULTIBOOT_H__

/* Includes */
#include "lib/types.h"

/* Multiboot Information Struture */
typedef struct MultibootInfo
{
	uint32_t Flags;
	uint32_t MemoryLow;
	uint32_t MemoryHigh;
	uint32_t BootDevice;
	uint32_t CmdLine;
	uint32_t ModuleCount;
	uint32_t ModuleAddr;
	union
	{
		struct
		{
			/* (a.out) Kernel Symbol table info */
			uint32_t TabSize;
			uint32_t StrSize;
			uint32_t Addr;
			uint32_t Pad;
		} a;
		struct
		{
			/* (ELF) Kernel section header table */
			uint32_t Num;
			uint32_t Size;
			uint32_t Addr;
			uint32_t Shndx;
		} e;
	} symbols;

	/* Memory Mappings */
	uint32_t MemoryMapLength;
	uint32_t MemoryMapAddr;

	/* Drive Info */
	uint32_t DrivesLength;
	uint32_t DrivesAddr;
	
	/* ROM Configuration Table */
	uint32_t ConfigTable;
	
	/* BootLoader Name */
	uint32_t BootLoaderName;

	/* APM Table */
	uint32_t ApmTable;

	/* Video Info */
	uint32_t VbeControllerInfo;
	uint32_t VbeModeInfo;
	uint32_t VbeMode;
	uint32_t VbeInterfaceSegment;
	uint32_t VbeInterfaceOffset;
	uint32_t VbeInterfaceLength;

} __attribute__((packed)) multiboot_info_t;

/* Flags */
#define MB_INFO_MEMORY			0x1
#define MB_INFO_BOOTDEVICE		0x2
#define MB_INFO_CMDLINE			0x4
#define MB_INFO_MODULES			0x8

/* The next two are mutually exclusive */
#define MB_INFO_AOUT			0x10
#define MB_INFO_ELF			0x20

/* More Symbols */
#define MB_INFO_MEM_MAP			0x40
#define MB_INFO_DRIVE_INFO		0x80
#define MB_INFO_CONFIG_TABLE		0x100
#define MB_INFO_BOOT_LDR_NAME		0x200
#define MB_INFO_APM_TABLE		0x400
#define MB_INFO_VIDEO_INFO		0x800

/* RAX must contain this */
#define MULTIBOOT_MAGIC			0x2BADBOO2

#endif
