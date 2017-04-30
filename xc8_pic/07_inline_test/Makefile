NUMCPUS=$(shell grep -c '^processor' /proc/cpuinfo)
NO_INCLUDE=true
CCARGS = -Iinclude
TARGETDIR=$(notdir $(shell pwd))
export 
all:
	nice $(MAKE) -j$(NUMCPUS) --load-average=$(NUMCPUS) -C .. $@
%:
	nice $(MAKE) -C .. $@
