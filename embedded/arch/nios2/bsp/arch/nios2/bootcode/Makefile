# $Id: Makefile 1 2014-09-24 14:40:57Z klugeflo $
# generate bootcode for nios
# not really sure, if we need it anymore
# generated code is not needed for project by default

# Simulate? (y/n)
SIMULATE= n

# read global configuration
include ../../../share/make.config

###############################################################################
# Variables for flags
###############################################################################

BASEDIR   = ../../..
LIBRARIES =

###############################################################################
# Files
###############################################################################

SRC = $(wildcard *.c)
PPASM = $(wildcard *.S)
ASM = $(PPASM:%.S=%.s)

OBJ = $(ASM:%.s=%.o) $(SRC:%.c=%.o)
DEP = $(ASM:%.s=%.d) $(SRC:%.c=%.d)

LIBDIR = $(BASEDIR)/lib/

###############################################################################
# Rules
###############################################################################

#
# NOTE: We don't link against libc! Maybe someone should try to do this once,
#	but for teaching OSes it's not that important
#

.PHONY: all
all: $(OBJ) #$(TARGET) #.elf $(TARGET).bin Makefile
	for f in $^; do cp $$f $(LIBDIR); done


# auto generate dependencies (see make manual)
%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$


#-include $(DEP)

.PHONY: mrproper
mrproper: clean

.PHONY: clean
clean:
	-$(RM) -f $(OBJ) $(DEP)
	-$(RM) -f $(MAPFILE)
	-$(RM) -f $(TARGET).elf $(TARGET).bin
	-$(RM) -f $(LIB_OS)
	-$(RM) -f *~ *.d.*
	for f in $(OBJ); do $(RM) -f $(LIBDIR)/$$f ; done
