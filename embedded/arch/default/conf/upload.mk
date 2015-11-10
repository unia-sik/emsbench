# $Id: upload.mk 201 2015-02-17 13:56:40Z klugeflo $
# Generic upload target

.PHONY: upload
upload: $(TARGET).elf
	@echo "Upload target"
