USE_LIBSP = n
USE_LIBDEV = n
DEBUG_OUTPUT=n

include ../conf/make.config

###############################################################################
# Flags
###############################################################################

BASEDIR = ..
LIBRARIES = 

###############################################################################
# Files
###############################################################################

SRC = $(wildcard *.c)
PPASM = $(wildcard *.S)
ASM = $(PPASM:%.S=%.s)

OBJ = $(ASM:%.s=%.o) $(SRC:%.c=%.o)
DEP = $(ASM:%.s=%.d) $(SRC:%.c=%.d)

LIB = ../lib/liboutput.a

CPP_DEF += -DSTM32F4
CFLAGS_USER += -Wno-unused-parameter

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
	-$(RM) -f $(LIB)
