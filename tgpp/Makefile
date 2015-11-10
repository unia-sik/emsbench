# $Id: Makefile 222 2015-03-06 14:35:28Z klugeflo $
# Building trace generator preprocessor

################################################################################

# Set the following variables for line numbers
# export ASAN_SYMBOLIZER_PATH=/usr/bin/llvm-symbolizer
# export ASAN_OPTIONS=symbolize=1
#SANITIZE = -fsanitize=address


################################################################################
# Flags

CPPFLAGS =
CFLAGS   = -O2 -g -Wall $(SANITIZE)
LDFLAGS  = $(SANITIZE) -lm

################################################################################
# Files

TARGET = tgpp

SRC = $(wildcard *.c)
OBJ = $(SRC:%.c=%.o)
DEP = $(OBJ:%.o=%.d)


################################################################################
# Rules

.PHONY: all
all: $(DEP) $(TARGET)


$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)


# auto generate dependencies (see make manual)
%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$


-include $(DEP)


.PHONY: clean
clean:
	$(RM) $(OBJ) $(DEP)
	$(RM) $(TARGET)
	$(RM) *.d.*


.PHONY: new
new: clean all
