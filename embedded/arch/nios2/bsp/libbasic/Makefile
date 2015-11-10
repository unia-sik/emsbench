# $Id: Makefile 803 2014-03-05 14:57:59Z klugeflo $
# Generate basic lib

# Simulate? (y/n)
SIMULATE= n

# read global configuration
include ../share/make.config

###############################################################################
# Flags
###############################################################################

BASEDIR   = ..
LIBRARIES =

###############################################################################
# Files
###############################################################################

SRC = $(wildcard *.c)
PPASM = $(wildcard *.S)
ASM = $(PPASM:%.S=%.s) $(wildcard *.s)

OBJ = $(ASM:%.s=%.o) $(SRC:%.c=%.o)
DEP = $(ASM:%.s=%.d) $(SRC:%.c=%.d)

TARGET = main

LIB = ../lib/libbasic.a

###############################################################################
# Rules
###############################################################################

.PHONY: all
all: lib


.PHONY: lib
lib: $(LIB)


$(LIB): $(OBJ)
	$(AR) -rc $@ $^

# auto generate dependencies (see make manual)
%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$


-include $(DEP)


.PHONY: clean
clean:
	-$(RM) -f $(OBJ) $(DEP)
	-$(RM) -f $(MAPFILE)
	-$(RM) -f *~ *.d.*

.PHONY: mrproper
mrproper: clean
	-$(RM) -f $(TARGET).elf $(TARGET).bin
	-$(RM) -f $(LIB)
