# $Id: Makefile 411 2015-10-06 13:36:28Z klugeflo $

include ./conf/make.config

SUBDIRS  = libopencm3 libub libbasic liboutput libutil libaeabi

.PHONY: all
all: subdirs

.PHONY: subdirs $(SUBDIRS)
subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ FP_FLAGS="$(HARD_FLOAT)"

.PHONY: clean
clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	-$(RM) -f lib/libopencm3_*
	-$(RM) -rf include/libopencm* share
