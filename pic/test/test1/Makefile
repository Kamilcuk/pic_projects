NAME=TEST01b

ALL:
	"gpasm" -DSTACK_MODEL_SMALL -D__STACK_MODEL_SMALL -o "$(NAME).o" -c $(NAME).ASM
	"gplink" -I"/usr/local/bin/../share/sdcc/lib/pic16" -I"/usr/local/share/sdcc/lib/pic16" -I"/usr/local/bin/../share/sdcc/non-free/lib/pic16" -I"/usr/local/share/sdcc/non-free/lib/pic16"   -w -r -o "$(NAME)"  "$(NAME).o" "libdev18f2550.lib" "libsdcc.lib"


