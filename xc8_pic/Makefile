ifndef TARGETDIR
$(error Define TARGETDIR ; cd into a directory and then run make)
endif

CC = $(wildcard /opt/microchip/xc8/*/bin/xc8)
CC += --chip=18F2550 
CC += --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug 
CC += --addrqual=require 
CC += --mode=pro -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file 
CC += --codeoffset=0x800 --rom=default,-0-7FF
CC += --output=default,-inhx032 
CC += --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib
CC += --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto
# allow eclipse project in main directory to find the file
PRE=xc8_pic/
CC += "--errformat=$(PRE)%f:%l: error: (%n) %s" 
CC += "--warnformat=$(PRE)%f:%l: warning: (%n) %s" 
CC += "--msgformat=$(PRE)%f:%l: note: (%n) %s"
CC += -G


CFLAGS := -Q --pass1 -I$(TARGETDIR)
LDFLAGS := 
OBJDIR := .obj
SRC := $(wildcard $(TARGETDIR)/*.c)

INCDIR = include
CFLAGS += -I$(INCDIR)
SRC += $(wildcard $(INCDIR)/*.c)
CFLAGS += -I$(INCDIR)/mla_usb/inc
SRC += $(INCDIR)/mla_usb/src/usb_device.c $(INCDIR)/mla_usb/src/usb_device_cdc.c
CFLAGS += -I$(INCDIR)/usbcdc
SRC += $(wildcard $(INCDIR)/usbcdc/*.c)

OBJ = $(addprefix $(OBJDIR)/,$(patsubst %.c,%.p1,$(SRC)))
HEX = $(TARGETDIR)/main.hex
VPATH = $(TARGETDIR)

all: $(OBJDIR) $(HEX)
$(OBJDIR):
	@mkdir -p $(dir $(OBJ))
$(HEX): $(OBJDIR) $(OBJ) $(wildcard *.h)
	$(CC) $(LDFLAGS) -o$(OBJDIR)/$(notdir $@) $(OBJ:.o=.p1)
	cp $(OBJDIR)/$(notdir $@) $@
$(OBJDIR)/%.p1: %.c
	$(CC) $(CFLAGS)  -o$@ $<
program_fsusb: $(HEX)
	sudo usb_modeswitch -Q -v FFFF -p 0100 -S
	while ! lsusb -d 04d8:000b; do :; done; sleep 0.1
	fsusb $(HEX)
	fsusb --reset
program_pk3cmd: $(HEX)
	while ! lsusb -d 04d8:900a; do :; done; sleep 0.1
	pk3cmd.sh $(HEX)
clean:
	cd $(OBJDIR) && rm -rf ./* || true
distclean: clean
	rmdir $(OBJDIR)
	rm -f $(TARGETDIR)/main.hex
.PHONY: $(OBJDIR) clean distclean
-include $(shell find $(OBJDIR) -name '*.d')


