# $Id: upload.mk 241 2015-03-12 16:01:06Z klugeflo $
# Generic upload target

BIN = $(TARGET).bin


%.bin: %.elf
	$(OBJC) -O binary $< $@


.PHONY: upload
upload: $(BIN)
	@echo "Upload target"
	st-flash write $< 0x08000000
