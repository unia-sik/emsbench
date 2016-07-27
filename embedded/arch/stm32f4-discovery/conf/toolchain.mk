# $Id: toolchain.mk 546 2016-07-15 06:51:19Z klugeflo $
# Toolchain used for building

CC   = arm-none-eabi-gcc
LD   = arm-none-eabi-gcc
OBJC = arm-none-eabi-objcopy
OBJD = arm-none-eabi-objdump

MACH_FLAGS = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mhard-float

CPPFLAGS += -I$(BASE)/arch/$(ARCH)/bsp/include -DSTM32F4 -DNEED_START
CFLAGS   += -Wextra $(MACH_FLAGS)
LDFLAGS  += -L$(BASE)/arch/$(ARCH)/bsp/lib -loutput -lub -lbasic -lopencm3_stm32f4 -lbasic -laeabi-cortexm0 -lutil -nostartfiles $(MACH_FLAGS) -T$(BASE)/arch/$(ARCH)/conf/stm32f4-discovery.ld

