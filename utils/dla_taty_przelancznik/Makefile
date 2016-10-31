
INSTALL_DIR=/usr/local
CFLAGS=-Wall -O2 $(shell pkg-config --libs --cflags libusb-1.0) -lpthread
CC=gcc
obj-o = przelancznik.o
przelancznik-o = 

OBJECTS = $($(obj-o:.o=)-o)
LIBRARIES = $($(obj-o:.o=)-lib)
.SECONDARY:

all: $(obj-o)

$(obj-o): %.o: %.c
	$(CC) $(CFLAGS) $($(@:.o=)-o) $< -o $(@:.o=)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

install:
	install $(obj-o:.o=) $(INSTALL_DIR)/bin

uninstall:
	cd $(INSTALL_DIR)/bin && rm -f $(obj) 

clean:
	rm -f *.o || true

distclean: clean
	rm $(obj-o) $($(obj-o:.o=)-o) || true

.SUFFIXES:
	MAKEFLAGS += -r
.PHONY: install uninstall clean distclean libs

	
