# Makefile for the kernel module

# Set the module name
MODULE := vm/Mips

FILES := _tlb.S mm_virt.c tlb.c mm_phys.c

MIPSSRC += $(patsubst %, $(MODULE)/%, $(FILES))

