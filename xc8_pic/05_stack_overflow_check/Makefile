NUMCPUS=$(shell grep -c '^processor' /proc/cpuinfo)
all:
	nice $(MAKE) -j$(NUMCPUS) --load-average=$(NUMCPUS) -C .. TARGETDIR=$(notdir $(shell pwd)) $@
%:
	nice $(MAKE) -C .. TARGETDIR=$(notdir $(shell pwd)) $@
