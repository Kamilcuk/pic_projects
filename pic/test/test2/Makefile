NAME=main

ALL:
	"gpasm" -DSTACK_MODEL_SMALL -D__STACK_MODEL_SMALL -o "$(NAME).o" -c $(NAME).asm
	"gplink" -I"/usr/bin/../share/sdcc/lib/pic16" -I"/usr/share/sdcc/lib/pic16" -I"/usr/bin/../share/sdcc/non-free/lib/pic16" -I"/usr/share/sdcc/non-free/lib/pic16"   -w -r -o "$(NAME)"  "$(NAME).o" "libdev18f2550.lib" "libsdcc.lib"


