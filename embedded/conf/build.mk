# $Id: build.mk 379 2015-09-23 14:06:26Z meixnean $
# Building of binary from sources and libs

# Requires: ARCH, APP, BASE, HAL_SRC, APP_SRC
# Optional: SUPP_SRC (must reside directly inside the build directory)

# Todo: [CPP|C|LD]FLAGS

###############################################################################
# show variables...
SHOW_VARIABLES = "true"

VARS_OLD := $(.VARIABLES)

###############################################################################
# toolchain

include $(BASE)/arch/$(ARCH)/conf/toolchain.mk

###############################################################################
# Files


include $(BASE)/arch/$(ARCH)/hal/files.mk
include $(BASE)/arch/$(ARCH)/hal-$(APP)/files.mk
include $(BASE)/$(APP)/files.mk


# C sources

THE_HAL_C_SRC = $(foreach file, $(HAL_C_SRC), $(BASE)/$(ARCH)/hal/$(file))
THE_HAP_C_SRC = $(foreach file, $(HAP_C_SRC), $(BASE)/$(ARCH)/hal-$(APP)/$(file))
THE_APP_C_SRC = $(foreach file, $(APP_C_SRC), $(BASE)/$(APP)/$(file))

C_OBJ = $(THE_HAL_C_SRC:$(BASE)/$(ARCH)/hal/%.c=hal/%.o) \
      $(THE_HAP_C_SRC:$(BASE)/$(ARCH)/hal-$(APP)/%.c=hal-$(APP)/%.o) \
      $(THE_APP_C_SRC:$(BASE)/$(APP)/%.c=$(APP)/%.o) \
      $(SUPP_C_SRC:%.c=%.o)

C_DEP = $(THE_HAL_C_SRC:$(BASE)/$(ARCH)/hal/%.c=hal/%.d) \
      $(THE_HAP_C_SRC:$(BASE)/$(ARCH)/hal-$(APP)/%.c=hal-$(APP)/%.d) \
      $(THE_APP_C_SRC:$(BASE)/$(APP)/%.c=$(APP)/%.d) \
      $(SUPP_C_SRC:%.c=%.d)


# S sources

THE_HAL_S_SRC = $(foreach file, $(HAL_S_SRC), $(BASE)/$(ARCH)/hal/$(file))
THE_HAP_S_SRC = $(foreach file, $(HAP_S_SRC), $(BASE)/$(ARCH)/hal-$(APP)/$(file))
S_OBJ = $(THE_HAL_S_SRC:$(BASE)/$(ARCH)/hal/%.S=hal/%.o) \
	$(THE_HAP_S_SRC:$(BASE)/$(ARCH)/hal-$(APP)/%.S=hal-$(APP)/%.o)

S_DEP = $(THE_HAL_S_SRC:$(BASE)/$(ARCH)/hal/%.S=hal/%.d) \
	$(THE_HAP_S_SRC:$(BASE)/$(ARCH)/hal-$(APP)/%.S=hal-$(APP)/%.d)

THE_HAL_SUPP_S_SRC = $(foreach file, $(HAL_SUPP_S_SRC), $(BASE)/$(ARCH)/hal/$(file))
SUPP_S_OBJ = $(THE_HAL_SUPP_S_SRC:$(BASE)/$(ARCH)/hal/%.S=hal/%.o) \


# Targets

OBJ = $(S_OBJ) $(C_OBJ)

TARGET = $(APP)-$(ARCH)

ELF = $(TARGET).elf
MAP = $(TARGET).map

###############################################################################
# Flags

CPPFLAGS += -I$(BASE)/arch/$(ARCH)/include -I$(BASE)/include
CFLAGS   += -Wall -O2 -g
LDFLAGS  += -Wl,-Map,$(MAP) # TODO!

###############################################################################
# ... show variables!

ifeq ($(SHOW_VARIABLES), "true")
$(foreach v,                                        \
  $(filter-out $(VARS_OLD) VARS_OLD,$(.VARIABLES)), \
  $(info $(v) = $($(v))))
endif

###############################################################################

.PHONY: all
all: $(ELF)

$(ELF): $(OBJ) $(SUPP_S_OBJ) #$(C_DEP) # $(C_OBJ)
#	@echo Building $@
#	@echo Depending on $^
#	$(LD) $^ $(LDFLAGS) -o $@
	$(LD) $(OBJ) $(LDFLAGS) -o $@



###############################################################################
# make C objects

hal/%.o: $(BASE)/arch/$(ARCH)/hal/%.c
	@echo Building $@...
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

hal-$(APP)/%.o: $(BASE)/arch/$(ARCH)/hal-$(APP)/%.c
	@echo Building $@...
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

$(APP)/%.o: $(BASE)/$(APP)/%.c
	@echo Building $@...
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

###############################################################################
# make S objects

hal/%.o: $(BASE)/arch/$(ARCH)/hal/%.S
	@echo Building $@...
	$(CC) $(CPPFLAGS) $(ASFLAGS) $(CFLAGS) -c -o $@ $<

hal-$(APP)/%.o: $(BASE)/arch/$(ARCH)/hal-$(APP)/%.S
	@echo Building $@...
	$(CC) $(CPPFLAGS) $(ASFLAGS) $(CFLAGS) -c -o $@ $<

###############################################################################
# auto generate dependencies (see make manual)

hal/%.d: $(BASE)/$(ARCH)/hal/%.c
	@set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

hal-$(APP)/%.d: $(BASE)/$(ARCH)/hal-$(APP)/%.c
	@set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

$(APP)/%.d: $(BASE)/$(APP)/%.c
	@set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

hal/%.d: $(BASE)/$(ARCH)/hal/%.S
	@set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

hal-$(APP)/%.d: $(BASE)/$(ARCH)/hal-$(APP)/%.S
	@set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$


-include $(C_DEP)
-include $(S_DEP)

-include $(BASE)/arch/$(ARCH)/conf/upload.mk


.PHONY: clean
clean:
	-$(RM) $(C_OBJ)
	-$(RM) $(C_DEP)
	-$(RM) $(ELF) $(MAP) $(BIN)

