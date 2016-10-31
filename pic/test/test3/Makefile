# Made by Kamil Cukrowski <kamil@dyzio.pl> licensed under BeerWare License
# makefile for uhcpic

PIC_TYPE = 18F2550
PIC_PORT = pic16

SDCC=sdcc
SDCC_FLAGS = -m$(PIC_PORT) -p$(PIC_TYPE) \
	-V --debug --verbose --std-sdcc99  \
	 --use-non-free \

CC=$(SDCC) $(SDCC_FLAGS)

objects = main.o 
clean = $(objects:.o=.asm)  $(objects:.o=.o) $(objects:.o=.adb) $(objects:.o=.lst)

ALL: 	main.hex

main.hex: $(objects) 
	$(SDCC) $(SDCC_FLAGS) $(objects)

$(objects): %.o: %.c ./*.c
	$(SDCC) -c $(SDCC_FLAGS) $< -o $@

dump:
	gpdasm -p$(PIC_TYPE) main.hex

install:
	sudo ~/Downloads/broccoli18-0.7/writepic ./main.hex


clean:
	rm main.adb main.asm main.cod main.hex main.lst main.map main.o

.PHONY: remove__once_functions
