# $Id: Makefile 19 2014-11-24 11:18:02Z klugeflo $
# generate libs for lab sessions

# read global configuration
include ./share/make.config

# removed libnet
SUBDIRS = libdrv libsim libbasic libosek libtool arch/$(ARCH) arch/$(ARCH)/bootcode
#LIBS = libbasic.a libdrv.a libnet.a libtool.a libosek.a libsimosek.a lib$(ARCH).a boot.o #libsim.a
# removed libnet.a
LIBS = libbasic.a libdrv.a lib$(ARCH).a boot.o #libsim.a
THE_LIBS = $(foreach lib,$(LIBS),lib/$(lib))

SOFCONF = nios2-configure-sof
SOF = ./share/niosuc.sof

.PHONY: all
#all: subdirs
all: $(THE_LIBS)



lib/libbasic.a:
	$(MAKE) -C libbasic

lib/libdrv.a:
	$(MAKE) -C libdrv

lib/lib$(ARCH).a:
	$(MAKE) -C arch/$(ARCH)

lib/boot.o:
	$(MAKE) -C arch/$(ARCH)/bootcode

#$(TEST): $(THE_LIBS)
#	$(MAKE) -C libosek 

.PHONY: subdirs
subdirs: $(SUBDIRS)

.PHONY: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@


.PHONY: clean
clean:
	for dir in $(SUBDIRS); do make -C $$dir clean; done

.PHONY: new
new: clean all


.PHONY: mrproper
mrproper: clean
	#for lib in $(THE_LIBS); do $(RM) $$lib; done
	for dir in $(SUBDIRS); do make -C $$dir mrproper; done

.PHONY: sofconf
sofconf: $(SOF)
	$(SOFCONF) $<
