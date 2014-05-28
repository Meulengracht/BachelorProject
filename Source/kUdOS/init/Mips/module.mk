# Makefile for the kernel module

# Set the module name
MODULE := init/Mips


FILES := _boot.S main.c 

MIPSSRC += $(patsubst %, $(MODULE)/%, $(FILES))

