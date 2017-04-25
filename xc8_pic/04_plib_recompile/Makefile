
CC = $(wildcard /opt/microchip/xc8/*/bin/xc8)
CC += --chip=18F2550 
CC += --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug 
CC += --addrqual=require 
CC += --mode=pro -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file 
CC += --codeoffset=0x800 --rom=default,-0-7FF
CC += --output=default,-inhx032 
CC += --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib
CC += --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto
CC += --warn=-3
CC += "--errformat=%f:%l: error: (%n) %s" 
CC += "--warnformat=%f:%l: warning: (%n) %s" 
CC += "--msgformat=%f:%l: note: (%n) %s"
CC += -G

CC += -Dfar=__far -Drom=const


CFLAGS := -Q --pass1
LDFLAGS := 
OBJDIR := .obj
CFLAGS += -I$(INCDIR)

OBJ = $(addprefix $(OBJDIR)/,$(patsubst %.c,%.p1,$(SRC)))
LIB=pic18-plib-htc-18f2550.lpp
all: $(LIB)
$(LIB): $(OBJ)
	$(CC) --output=lpp -o$@ $(OBJ)
$(OBJDIR)/%.p1: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS)  -o$@ $<
$(OBJDIR)/%.p1: %.asm
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS)  -o$@ $< ; ?? THIS DOES NOT WORK (YET!)

