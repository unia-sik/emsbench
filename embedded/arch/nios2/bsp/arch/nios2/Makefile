# $Id: Makefile 803 2014-03-05 14:57:59Z klugeflo $
# generate nios2 boot code

# Simulate? (y/n)
SIMULATE= n

# read global configuration
include ../../share/make.config

###############################################################################
# Variables for flags
###############################################################################

BASEDIR   = ../..
LIBRARIES =

###############################################################################
# Files
###############################################################################

SRC = $(wildcard *.c)
PPASM = $(wildcard *.S)
ASM = $(PPASM:%.S=%.s)

OBJ = $(ASM:%.s=%.o) $(SRC:%.c=%.o)
DEP = $(ASM:%.s=%.d) $(SRC:%.c=%.d)

TARGET = main

LIB = $(BASEDIR)/lib/lib$(ARCH).a

###############################################################################
# Rules
###############################################################################

.PHONY: all
all: lib


.PHONY: lib
lib: $(LIB)


$(LIB): $(OBJ)
#	@echo "(AR) $(CCLIB)"
	$(AR) -rc $@ $^
# not needed
#	make -C bootcode

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
