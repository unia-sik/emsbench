# $Id: build.mk 546 2016-07-15 06:51:19Z klugeflo $
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

APP_HAL = hal-$(HAL_APP)

include $(BASE)/arch/$(ARCH)/hal/files.mk
include $(BASE)/arch/$(ARCH)/$(APP_HAL)/files.mk
include $(BASE)/$(APP)/files.mk


# C sources

THE_HAL_C_SRC = $(foreach file, $(HAL_C_SRC), $(BASE)/$(ARCH)/hal/$(file))
THE_HAP_C_SRC = $(foreach file, $(HAP_C_SRC), $(BASE)/$(ARCH)/$(APP_HAL)/$(file))
THE_APP_C_SRC = $(foreach file, $(APP_C_SRC), $(BASE)/$(APP)/$(file))

C_OBJ = $(THE_HAL_C_SRC:$(BASE)/$(ARCH)/hal/%.c=hal/%.o) \
      $(THE_HAP_C_SRC:$(BASE)/$(ARCH)/$(APP_HAL)/%.c=$(APP_HAL)/%.o) \
      $(THE_APP_C_SRC:$(BASE)/$(APP)/%.c=$(APP)/%.o) \
      $(SUPP_C_SRC:%.c=%.o)

C_DEP = $(THE_HAL_C_SRC:$(BASE)/$(ARCH)/hal/%.c=hal/%.d) \
      $(THE_HAP_C_SRC:$(BASE)/$(ARCH)/$(APP_HAL)/%.c=$(APP_HAL)/%.d) \
      $(THE_APP_C_SRC:$(BASE)/$(APP)/%.c=$(APP)/%.d) \
      $(SUPP_C_SRC:%.c=%.d)


# S sources

THE_HAL_S_SRC = $(foreach file, $(HAL_S_SRC), $(BASE)/$(ARCH)/hal/$(file))
THE_HAP_S_SRC = $(foreach file, $(HAP_S_SRC), $(BASE)/$(ARCH)/$(APP_HAL)/$(file))
S_OBJ = $(THE_HAL_S_SRC:$(BASE)/$(ARCH)/hal/%.S=hal/%.o) \
	$(THE_HAP_S_SRC:$(BASE)/$(ARCH)/$(APP_HAL)/%.S=$(APP_HAL)/%.o)

S_DEP = $(THE_HAL_S_SRC:$(BASE)/$(ARCH)/hal/%.S=hal/%.d) \
	$(THE_HAP_S_SRC:$(BASE)/$(ARCH)/$(APP_HAL)/%.S=$(APP_HAL)/%.d)

THE_HAL_SUPP_S_SRC = $(foreach file, $(HAL_SUPP_S_SRC), $(BASE)/$(ARCH)/hal/$(file))
SUPP_S_OBJ = $(THE_HAL_SUPP_S_SRC:$(BASE)/$(ARCH)/hal/%.S=hal/%.o) \


# Targets

OBJ = $(S_OBJ) $(C_OBJ)

TARGET = $(APP)-$(ARCH)

ELF = $(TARGET).elf
MAP = $(TARGET).map
DUMP = $(TARGET).dump

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
all: $(ELF) $(DUMP)

$(ELF): $(OBJ) $(SUPP_S_OBJ) #$(C_DEP) # $(C_OBJ)
#	@echo Building $@
#	@echo Depending on $^
#	$(LD) $^ $(LDFLAGS) -o $@
	$(LD) $(OBJ) $(LDFLAGS) -o $@

$(DUMP): $(ELF)
	$(OBJD) $< -S > $@

###############################################################################
# make C objects

hal/%.o: $(BASE)/arch/$(ARCH)/hal/%.c
	@echo Building $@...
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

$(APP_HAL)/%.o: $(BASE)/arch/$(ARCH)/$(APP_HAL)/%.c
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

$(APP_HAL)/%.o: $(BASE)/arch/$(ARCH)/$(APP_HAL)/%.S
	@echo Building $@...
	$(CC) $(CPPFLAGS) $(ASFLAGS) $(CFLAGS) -c -o $@ $<

###############################################################################
# auto generate dependencies (see make manual)

hal/%.d: $(BASE)/$(ARCH)/hal/%.c
	@set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

$(APP_HAL)/%.d: $(BASE)/$(ARCH)/$(APP_HAL)/%.c
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

$(APP_HAL)/%.d: $(BASE)/$(ARCH)/$(APP_HAL)/%.S
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

