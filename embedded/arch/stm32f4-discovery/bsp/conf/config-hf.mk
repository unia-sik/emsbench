###############################################################################
# Global flags
###############################################################################

ARCH = arm-none
PLATTFORM = STM32F4

###############################################################################
# Binaries
###############################################################################

AR   = $(ARCH)-eabi-ar
AS   = $(ARCH)-eabi-as
CC   = $(ARCH)-eabi-gcc
LD   = $(ARCH)-eabi-g++
OBJC = $(ARCH)-eabi-objcopy
OBJD = $(ARCH)-eabi-objdump

MAKE = make

###############################################################################
# Flags
###############################################################################

CPP_DEF += -D$(PLATTFORM)

LIBCM3 = -lopencm3_stm32f4

ifeq ($(DEBUG_OUTPUT),y)
	CPP_DEF += -D__DEBUG__
endif

LDSCRIPT = $(BASEDIR)/conf/stm32f4-discovery.ld

PLATFLAGS= -mcpu=cortex-m4 -mthumb -mfpu=vfp -mhard-float -nostartfiles

ASFLAGS  = -g
CPPFLAGS = -I$(BASEDIR)/include $(CPP_DEF) $(CPP_OWN)
CFLAGS   = -g -Wall -Wextra -O0 $(PLATFLAGS) $(CFLAGS_USER)
CXXFLAGS = $(CFLAGS)
MAP      = -Wl,-Map,$(TARGET).map
LDFLAGS  = -T$(LDSCRIPT) $(MAP) $(PLATFLAGS) $(LDFLAGS_USER) -L$(BASEDIR)/lib $(LIBRARIES) $(LIBCM3)
