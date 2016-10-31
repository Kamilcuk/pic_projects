# Made by Kamil Cukrowski <kamil@dyzio.pl> licensed under BeerWare License
# makefile for crt0

PIC_TYPE = 18F2550
PIC_PORT = pic16
lkr_FILE = ../lkr/18f2550.lkr
obj-o = crt0.o

# comma separated!
LINKER_FLAGS = -s$(lkr_FILE),-m
SDCC=sdcc
SDCC_FLAGS = -m$(PIC_PORT) -p$(PIC_TYPE) \
	-V --debug --verbose --std-sdcc99  \
	--optimize-cmp --optimize-df --use-non-free \
	--compile-only

CC=$(SDCC) $(SDCC_FLAGS)
clean = $(obj-o:.o=.asm)  $(obj-o:.o=.adb) $(obj-o:.o=.lst)

ALL: 	crt0.o

$(ob-o): %.o: %.c
	$(SDCC) -c $(SDCC_FLAGS) $< -o $@

clean:
	rm $(clean)


