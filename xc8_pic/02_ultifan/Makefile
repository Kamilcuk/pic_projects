PLIB_SRC= Timers i2c CCP
NUMCPUS=$(shell grep -c '^processor' /proc/cpuinfo)
TARGETDIR=$(notdir $(shell pwd))
export
all:
	$(MAKE) -j$(NUMCPUS) --load-average=$(NUMCPUS) -C .. $@
%:
	$(MAKE) -j$(NUMCPUS) --load-average=$(NUMCPUS) -C .. $@
