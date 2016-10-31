# Made by Kamil Cukrowski <kamil@dyzio.pl> licensed under BeerWare License
# makefile for uhcpic

PIC_TYPE = 18F2550
PIC_PORT = pic16
lkr_FILE = ./18f2550.lkr
crt_FILE = ./startup/crt0.o


# comma separated!
LINKER_OPTIONS = -s$(lkr_PIC_TYPE).lkr,-m

SDCC=sdcc
SDCC_FLAGS = -m$(PIC_PORT) -p$(PIC_TYPE) \
	-V --debug --verbose --std-sdcc99  \
	--optimize-cmp --optimize-df --use-non-free \
	--use-crt=$(crt_FILE) --stack-auto \
	-Wl-s$(lkr_FILE),-m 

CC=$(SDCC) $(SDCC_FLAGS)

objects = main.o
clean = $(objects:.o=.asm) $(objects:.o=.o) $(objects:.o=.adb) $(objects:.o=.lst)

ALL: 	main.hex

main.hex: $(crt_FILE) $(objects)  $(lkr_FILE)
	$(SDCC) $(SDCC_FLAGS) $(objects)

$(crt_FILE): $(crt_FILE:.o=.c)
	$(SDCC) $(SDCC_FLAGS) -c $< -o $@


$(objects): %.o: %.c ./*.c
	$(SDCC) -c $(SDCC_FLAGS) $< -o $@

remove__once_functions:

clean:
	rm $(crt_FILE:.o=.asm)  $(crt_FILE:.o=.o) $(crt_FILE:.o=.adb) $(crt_FILE:.o=.lst)
	rm main.adb main.asm main.cod main.hex main.lst main.map main.o
	rm $(clean)

.PHONY: remove__once_functions
