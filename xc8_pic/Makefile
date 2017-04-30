
ifndef TARGETDIR
TARGETDIR=./TARGETDIR
$(notice TARGETDIR not defined ; cd into a directory and then run make. Default TARGETDIR=$(TARGETDIR))
endif

CCARGS ?=
CC = @./xc8.sh $(CCARGS)

OBJDIR := .obj
CFLAGS := -Q --pass1 -I$(TARGETDIR)
ASMFLAGS := --pass1
LDFLAGS := --memorysummary $(OBJDIR)/memoryfile.xml

SRC ?=
SRC += $(wildcard $(TARGETDIR)/*.c) $(wildcard $(TARGETDIR)/*.as)

INCDIR = include

ifndef NO_INCLUDE
CFLAGS += -I$(INCDIR)
SRC += $(wildcard $(INCDIR)/*.c)

CFLAGS += -I$(INCDIR)/mla_usb/inc
SRC += $(INCDIR)/mla_usb/src/usb_device.c $(INCDIR)/mla_usb/src/usb_device_hid.c

CFLAGS += -I$(INCDIR)/usbhid_stdio
SRC += $(wildcard $(INCDIR)/usbhid_stdio/*.c)
endif

ifdef PLIB_SRC
CFLAGS += -I$(INCDIR)/plib
SRC += $(wildcard $(addsuffix /*.c,$(addprefix plib/, $(PLIB_SRC))))
endif

OBJ := $(addprefix $(OBJDIR)/, $(patsubst %.as,%.obj, $(patsubst %.c,%.p1, $(SRC) ) ) )
HEX := $(TARGETDIR)/main.hex
VPATH = $(TARGETDIR)

all: $(HEX)
$(HEX): $(OBJ)
	$(CC) $(LDFLAGS) -o$(OBJDIR)/$(notdir $@) $(OBJ:.o=.p1)
	cp $(OBJDIR)/$(notdir $@) $@

$(OBJDIR)/%.p1: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o$@ $<

$(OBJDIR)/%.obj: %.as
	mkdir -p $(dir $@)
	$(CC) $(ASMFLAGS) -o$@ $<

program_fsusb: $(HEX)
	./program_fsusb.sh $(HEX)

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


