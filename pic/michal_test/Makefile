# Made by Kamil Cukrowski <kamil@dyzio.pl> licensed under BeerWare License
# makefile for uhcpic
PWD = $(shell pwd)
PIC_TYPE = 18F2550
PIC_PORT = pic16
PROJDIR = ../
lkr_FILE = ../include/lkr/18f2550_bootloader.lkr
include = ../include/

obj-o = main.o
main-o = $(patsubst %.c,%.o,$(filter-out main.c,$(wildcard *.c))) 
main-o += ../include/usbcdc/usbcdc.o

# comma separated!
LINKER_FLAGS = -s$(lkr_FILE),--map,libc18f.lib,-O2,--no-cinit-warnings,-S2
SDCC=sdcc
OPTIMIZE_FLAGS = --peep-asm --peep-return --opt-code-speed
DEBUG_FLAGS = --debug --fverbose-asm
SDCC_FLAGS = -m$(PIC_PORT) -p$(PIC_TYPE) --Werror $(DEBUG_FLAGS) $(OPTIMIZE_FLAGS) \
	--std-sdcc99 --use-crt=crt0iz.o \
	 --use-non-free -I$(include) -I./\
	-Wl$(LINKER_FLAGS)


CC = $(SDCC)
CFLAGS = $(SDCC_FLAGS)

obj-hex = $(obj-o:.o=.hex)
OBJECTS = $($(obj-o:.o=)-o) 
LIBRARIES = $($(obj-o:.o=)-lib)

all: 	$(obj-hex) stat
.SECONDARY:

$(obj-hex): %.hex: %.c $(OBJECTS) $(LIBRARIES)
	$(CC) $(CFLAGS) -c $(<:.hex=.c) -o $(@:.hex=.o)
	$(CC) $(CFLAGS) $(patsubst  %,-Wllib%, $(LIBRARIES)) $(OBJECTS) $(@:.hex=.o) -o $(@:.hex=)
	../scripts/changeVectorsLocationsInHex.sh $(@:.o=.hex)

%.lib: %.o
	gplib -c lib$@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

stat: $(obj-hex)
	@echo -e "Statistics:\n^ hex lines count $(<:.o=.hex) : $$(gpdasm -p18f2550 $(<:.o=.hex) | wc -l )\n^ hex chars count $(<:.o=.hex) : $$(gpdasm -p18f2550 $(<:.o=.hex) | wc -c )"

reprogram: $(obj-o:.o=.hex)
	if lsusb | grep -q "ID ffff:0100"; then sudo usb_modeswitch -v FFFF -p 0100 -S; fi
	while ! lsusb | grep -q "ID 04d8:000b"; do :; done;
	sudo /home/kamil/bin/fsusb ./main.hex
	sudo /home/kamil/bin/fsusb --reset

clean:
	rm main.hex main.cod main.map || true
	rm $(obj-o) $(obj-o:.o=.asm) $(obj-o:.o=.adb) $(obj-o:.o=.lst) $(main-o:.o=.asm) $(main-o:.o=.adb) $(main-o) $(main-o:.o=.lst) || true

# disable default rules - we do everything ourself
.SUFFIXES:
	MAKEFLAGS += -r

.PHONY: stat clean

