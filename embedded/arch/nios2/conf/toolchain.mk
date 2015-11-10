# $Id: toolchain.mk 302 2015-06-09 12:29:27Z meixnean $
# Toolchain used for building

SYSTEM = nios2
BOARD = de2-70

AR   = $(ARCH)-elf-ar
AS   = $(ARCH)-elf-as
CC   = $(ARCH)-elf-gcc
LD   = $(ARCH)-elf-g++
OBJC = $(ARCH)-elf-objcopy
OBJD = $(ARCH)-elf-objdump

CPPFLAGS += -I$(BASE)/arch/$(ARCH)/bsp/include -I$(BASE)/arch/$(ARCH)/bsp/include/arch/nios2 -D__BOARD=$(BOARD) -D__ALTERA_BOARD $(DEBUG_FLAG)
LDFLAGS += -L$(BASE)/arch/$(ARCH)/bsp/lib -lnios2 -ldrv -lbasic -msys-crt0='hal/crt0.o' -Bstatic -T$(BASE)/arch/nios2/conf/altera-de2-70-nios2.ld
