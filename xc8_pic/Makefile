# Author: Kamil Cukrowski
#
# compilation takes place in OBJDIR
#
# include TARGETDIR/Makefile
# Docu: http://scottmcpeak.com/autodepend/autodepend.html
#
ifndef TARGETDIR
 TARGETDIR := $(notdir $(realpath TARGETDIR))
 $(info TARGETDIR not defined. Default TARGETDIR=[$(TARGETDIR)])
 include ${TARGETDIR}/Makefile
endif

# config
OBJDIR := .obj

# default CCARGS - codeoffset in 0x800, remember to set codeoffset=0x000 for simlation
CCARGS ?= --codeoffset=0x800

# xc8 flags and config
CC := @./xc8.sh $(CCARGS)
AS := @./xc8.sh $(CCARGS)
CFLAGS  := --pass1 -Q
ASFLAGS := --pass1 -Q
LDFLAGS := --memorysummary $(OBJDIR)/memoryfile.xml

############################## config ####################################

### INCLUDE_SOURCES := systick hd55780
# will include all .c files in INCDIR with these names
### PLIB_SOURCES := Timers CCP i2c
# list of directories in PLIB_SOURCES_DIR to compile
# will compile all .c and .as files inside this directory
### USBHID_STDIO :=
# will compile support for USBHID_STDIO 

# in user TARGETDIR/Makefile define SOURCES for additional files
SOURCES ?=
SOURCES += $(wildcard $(addprefix $(TARGETDIR),/*.c /*.as))
CFLAGS  += -I$(TARGETDIR)

# my include directory
INCDIR ?= include

# Function to check if files in the variable name exist.
# First parameter is the variable NAME to expands to lists of files to check for exsistence
define CHECK_FILES_EXISTS_FUNC
  $(foreach p,$($(1)),$(if $(wildcard $(p)),,
    $(warning $(1) defines non existent targets: $(p) does not exist!) $(eval err:=yes)
  ))
  $(if $(err),
    $(if $(2),
      $(info $(1) can be one of the following:)
      $(foreach p,$(addprefix    ,$(filter $(INCLUDE_SOURCES_LIST),$(2))),$(info $(p)))
    ,) 
    $(error Aborting)
  ,)
endef

ifndef NO_INCLUDE
  CFLAGS  += -I$(INCDIR) -I$(INCDIR)/plib
  ifdef INCLUDE_ALL_SOURCES
    SOURCES += $(wildcard $(INCDIR)/*.c)
  else
    ifdef INCLUDE_SOURCES
      INCLUDE_SOURCES_LIST := $(addprefix $(INCDIR)/, $(addsuffix .c, $(INCLUDE_SOURCES) ) )
      $(call CHECK_FILES_EXISTS_FUNC,INCLUDE_SOURCES_LIST,$(notdir $(basename $(wildcard $(INCDIR)/*.c))))
      SOURCES += $(INCLUDE_SOURCES_LIST)
    endif
  endif
endif

ifdef PLIB_SOURCES
  # add all .c and .as files to SOURCES that are in directories under $(PLIB_SOURCES_DIR)/$(PLIB_SOURCES)
  PLIB_SOURCES_DIR := plib_sources
  PLIB_SOURCES_DIR_LIST := $(PLIB_SOURCES:%=$(PLIB_SOURCES_DIR)/%)
  $(call CHECK_FILES_EXISTS_FUNC,PLIB_SOURCES_DIR_LIST,$(notdir $(wildcard $(PLIB_SOURCES_DIR)/*)))
  SOURCES += $(wildcard $(PLIB_SOURCES_DIR_LIST:%=%/*.c) $(PLIB_SOURCES_DIR_LIST:%=%/*.as) )
endif

ifdef USBHID_STDIO
  CFLAGS  += -I$(INCDIR)/usbhid_stdio -I$(INCDIR)/mla_usb/inc
  SOURCES += $(wildcard $(INCDIR)/usbhid_stdio/*.c)
  SOURCES += $(INCDIR)/mla_usb/src/usb_device.c $(INCDIR)/mla_usb/src/usb_device_hid.c
endif

######################################3 eof config ##############################

TARGET           := $(TARGETDIR)/main
TARGET_OBJECT    := $(OBJDIR)/$(notdir $(TARGET))
OBJECTS          := $(addprefix $(OBJDIR)/,$(patsubst %.as,%.obj,$(patsubst %.c,%.p1,$(SOURCES))))
DEPENDENCY_FILES := $(patsubst %.p1,%.d,$(filter %.p1,$(OBJECTS)))
-include $(DEPENDENCY_FILES)

.DEFAULT_GOAL :=
all: $(TARGET).hex
$(TARGET).hex: $(TARGET_OBJECT).hex
	cp $< $@
	
$(TARGET_OBJECT).hex $(TARGET_OBJECT).elf: $(OBJECTS)
	$(CC) $(LDFLAGS) -o$(basename $@).hex $^

$(OBJDIR)/%.p1: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o$(basename $@) $<
	@cp -f $(basename $@).d $(basename $@).d.tmp
	@sed -e 's/.*://' -e 's/\\$$//' < $(basename $@).d.tmp | fmt -1 | \
		sed -e '1i\\' -e 's/^ *//' -e 's/$$/:/' >> $(basename $@).d
	@rm -f $*.d.tmp

$(OBJDIR)/%.obj: %.as
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -o$@ $<

hexinfo: $(TARGET_OBJECT).hex
	./hexinfo.sh $<
simulate: $(TARGET_OBJECT).elf
	./simulate.sh $<
program_fsusb: $(TARGET_OBJECT).hex
	./program_fsusb.sh $<
program_pk3cmd: $(TARGET_OBJECT).hex
	while ! lsusb -d 04d8:900a; do sleep 0.1; done; sleep 0.1;
	pk3cmd.sh $<
print-%:
	$(info )
	$(info $* is $(flavor $*) variable set to [$($*)]) @true

clean:
	[ -d $(OBJDIR) ] && cd $(OBJDIR) && rm -rf ./* || true
distclean: clean
	rmdir $(OBJDIR)
	rm -f $(TARGETDIR)/main.hex

.PHONY: clean distclean hexinfo simulate program_fsusb program_pk3cmd print-%

