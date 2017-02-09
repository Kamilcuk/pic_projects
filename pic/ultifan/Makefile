# Made by Kamil Cukrowski <kamil@dyzio.pl> licensed under BeerWare License
# makefile for uhcpic
PWD = $(shell pwd)
PIC_TYPE = 18F2550
PIC_PORT = pic16
lkr_FILE = ../include/lkr/18f2550_bootloader.lkr
include = ../include/

obj-o = main.o 
main-o = ../include/usbcdc/usbcdc.o

# comma separated!
LINKER_FLAGS = -s$(lkr_FILE),--map,libc18f.lib,-O2,--no-cinit-warnings
SDCC=sdcc
OPTIMIZE_FLAGS = --peep-asm --peep-return --opt-code-speed
DEBUG_FLAGS = --debug --fverbose-asm
SDCC_FLAGS = -m$(PIC_PORT) -p$(PIC_TYPE) $(DEBUG_FLAGS) $(OPTIMIZE_FLAGS) \
	--std-sdcc99 --use-crt=crt0iz.o \
	 --use-non-free -I$(include) -I./\
	-Wl$(LINKER_FLAGS) \
	-DUSBCDC_ID_VENDOR="0x00,0x01" \
	-DUSBCDC_ID_PRODUCT="0x00,0x01"


CC = $(SDCC)
CFLAGS = $(SDCC_FLAGS)

OBJECTS = $($(obj-o:.o=)-o) 
LIBRARIES = $($(obj-o:.o=)-lib)

all: 	$(obj-o) stat
	echo $($(filter-out main.c,$(wildcard *.c)):.c=.o)
.SECONDARY:

$(obj-o): %.o: %.c $(OBJECTS) $(LIBRARIES)
	$(CC) $(CFLAGS) -c $< -o $@
	$(CC) $(CFLAGS) $(patsubst  %,-Wllib%, $(LIBRARIES)) $(OBJECTS) $@ -o $(@:.o=)
	../scripts/changeVectorsLocationsInHex.sh $(@:.o=.hex)

%.lib: %.o
	gplib -c lib$@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

stat: $(obj-o)
	echo -e "Statistics:\n^ hex lines count $(<:.o=.hex) : $$(gpdasm -p18f2550 $(<:.o=.hex) | wc -l )\n^ hex chars count $(<:.o=.hex) : $$(gpdasm -p18f2550 $(<:.o=.hex) | wc -c )"

reprogram:
	sudo usb_modeswitch -W -v 0100 -p 0100 -S
	sleep 7
	make clean
	make -j5 all
	fsusb ./main.hex
	fsusb --reset

clean:
	rm main.hex main.cod main.map || true
	rm main.asm main.adb main.o main.lst || true
	rm $(main-o:.o=.asm) || true
	rm $(main-o:.o=.adb) || true
	rm $(main-o:.o=.o) || true
	rm $(main-o:.o=.lst) || true

# disable default rules - we do everything ourself
.SUFFIXES:
	MAKEFLAGS += -r

.PHONY: stat clean
