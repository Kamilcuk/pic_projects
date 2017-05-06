
PLIB_SOURCES = Timers
CCARGS =
SOURCES = include/systick.c

ifndef TARGETDIR
TARGETDIR = $(notdir $(abspath .))
NUMCPUS   = $(shell grep -c '^processor' /proc/cpuinfo)
export
all: ; nice $(MAKE) -j$(NUMCPUS) --load-average=$(NUMCPUS) -C .. $@ 
%:   ; nice $(MAKE) -j$(NUMCPUS) --load-average=$(NUMCPUS) -C .. $@
endif
