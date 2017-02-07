# Made by Kamil Cukrowski <kamil@dyzio.pl> licensed under BeerWare License
# makefile for uhcpic
PWD = $(shell pwd)
PIC_TYPE = 18F2550
PIC_PORT = pic16
lkr_FILE = ./18f2550_bootloader.lkr
include = ../../include/

obj-o = main.o 
main-o = ../../include/usb/usb.o crt0iz_0800.o

# comma separated!
LINKER_FLAGS = -s$(lkr_FILE),--map,libc18f.lib,--no-cinit-warnings
SDCC=sdcc
OPTIMIZE_FLAGS = --peep-asm --peep-return --opt-code-speed
DEBUG_FLAGS = --debug --fverbose-asm # --Werror # -V --verbose # --cyclomatic --dump-graphs
SDCC_FLAGS = -m$(PIC_PORT) -p$(PIC_TYPE) $(DEBUG_FLAGS) $(OPTIMIZE_FLAGS) \
	--std-sdcc99 --no-crt \
	 --use-non-free -I$(include) -I./\
	-Wl$(LINKER_FLAGS)

CC = $(SDCC)
CFLAGS = $(SDCC_FLAGS)
# strip assemble compiler command from sdcc  
ASMC := $(shell temp=`mktemp -d`; echo 'void main(){return;}' > $$temp/a.c ; $(CC) $(CFLAGS) -V -c $$temp/a.c -o $$temp/a.o | grep gpasm | sed -e "s:-o $$temp/a.o -c $$temp/a.asm: -c :" -e "s:+ \"::" -e "s:\"::"; rm -r $$temp || true ; )

OBJECTS = $($(obj-o:.o=)-o) 
LIBRARIES = $($(obj-o:.o=)-lib)

ALL: 	$(obj-o)
.SECONDARY:

$(obj-o): %.o: %.c $(OBJECTS) $(LIBRARIES)
	$(CC) $(CFLAGS) -c $(@:.o=.c) -o $@
	$(CC) $(CFLAGS) $(patsubst  %,-Wllib%, $(LIBRARIES)) $(OBJECTS) $@ -o $(@:.o=)

%.lib: %.o
	gplib -c lib$@ $<

%.o: %.asm
	$(ASMC) $< -o $@ 

%.asm: %.c 
	$(CC) $(CFLAGS) -S $< -o $@
	$(include)/removelocalunusedfunctions.sh $@

stat: $(obj-o)
	echo memory lines to be programmed for $(<.o=.hex): $$(gpdasm -p18f2550 $(<:.o=.hex) | wc -l )

clean:
	rm main.hex main.cod main.map || true
	rm main.asm main.adb main.o main.lst || true
	rm $(main-o:.o=.asm) || true
	rm $(main-o:.o=.adb) || true
	rm $(main-o:.o=.o) || true
	rm $(main-o:.o=.lst) || true
	
install:
	sudo ~/Downloads/broccoli18-0.7/writepic ./main.hex

# disable default rules - we do everything ourself
.SUFFIXES:
	MAKEFLAGS += -r

.PHONY: stat clean install 
