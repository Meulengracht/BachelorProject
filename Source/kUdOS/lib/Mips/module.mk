# Makefile for the lib module

# Set the module name
MODULE := lib/Mips

FILES := rand.S

MIPSSRC += $(patsubst %, $(MODULE)/%, $(FILES))
