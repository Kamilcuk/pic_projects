# What?

File compile.sh recompiles plib peripheral libraries.

# Why?

```
make -C .. TARGETDIR=02_ultifan all
make[1]: Entering directory '/home/projects/allrepos/pic_projects/xc8_pic'
/opt/microchip/xc8/v1.41/bin/xc8 --chip=18F2550  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug  --addrqual=require  --mode=pro -P -N255 --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file  --codeoffset=0x800 --rom=default,-0-7FF --output=default,-inhx032  --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto --warn=-3 "--errformat=%f:%l: error: (%n) %s"  "--warnformat=%f:%l: warning: (%n) %s"  "--msgformat=%f:%l: note: (%n) %s" -G  -o.obj/main.hex .obj/02_ultifan/common.p1 .obj/02_ultifan/main.p1 .obj/include/morse.p1 .obj/include/printft.p1 .obj/include/mla_usb/src/usb_device.p1 .obj/include/mla_usb/src/usb_device_hid.p1 .obj/include/usbhid_stdio/usbhid_stdio.p1 .obj/include/usbhid_stdio/usb_descriptors.p1 .obj/include/usbhid_stdio/usb_events.p1
XCLM: Failed to elevate privilege - is the XCLM binary setuid-root?
Microchip MPLAB XC8 C Compiler (Free Mode) V1.41
Build date: Jan 24 2017
Part Support Version: 1.41
Copyright (C) 2017 Microchip Technology Inc.
License type: Node Configuration

:: note: (1233) Employing 18F2550 errata work-arounds:
:: note: (1234)  * Corrupted fast interrupt shadow registers
:: warning: (1273) Omniscient Code Generation not available in Free mode
XCLM: Failed to elevate privilege - is the XCLM binary setuid-root?
/opt/microchip/xc8/v1.41/include/pic18f2550.h:4155: error: (1098) conflicting declarations for variable "_PIR1bits" (/opt/microchip/xc8/v1.41/include/pic18f2550.h:3520)
(908) exit status = 1
make[1]: *** [Makefile:46: 02_ultifan/main.hex] Error 1
make[1]: Leaving directory '/home/projects/allrepos/pic_projects/xc8_pic'
make: *** [Makefile:2: all] Error 2
```

