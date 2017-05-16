# pic_projects

My Microchip PIC18F2550 related projects.  
Folders:  

```
./xc8_pic          - folder with projects using xc8 compiler
./xc8_pic/[0-9]{2} - one folder per project
./xc8_pic/include  - include directory
./utils            - utilities used on the host side to communicate with pic projects
./kamiltech.hwdb   - udev database with usb vendor numbers
```

## Compile

Makefile, make.  
To compile projects under xc8_pic directory you need xc8 compiler.   

### sdcc notice

I have used sdcc for many projects, but in the long way i missed good usb implementation using sdcc. Microchip has it's own usb stack for XC8 and C18 compilers, and that firmware supports all usb related actions (attaching, deattaching, disconecting) ex. So i switched to XC8 and will never go back sdcc and i don't regret it, XC8 is quite OK.  

### PIC18F2550 usb firmware

Under ./xc8_pic/include/mla_usb is git submodule with usb drivers from https://github.com/MicrochipTech/mla_usb  
Under ./xc8_pic/include/usbhid_stdio is printf and getchar implementation using USB HID device. File ./xc8_pic/include/usbhid_stdio/usbhid_stdio.c takes care about buffering, transmission and receiving.  

## Flash new hex

### Flash new hex with bootloader

Check bootloader is running:
```
# lsusb  | grep 000b
Bus 001 Device 003: ID 04d8:000b Microchip Technology, Inc. PIC18F2550 (32K Flashable 10 Channel, 10 Bit A/D USB Microcontroller)
```

Download utility for flashing with bootloader:
```
git clone https://github.com/Kamilcuk/pic-PICDEM-fsusb
cd pic-PICDEM-fsusb
make
```
**or**
```
wget https://github.com/Kamilcuk/pic-PICDEM-fsusb/releases/download/0.1/fsusb
chmod +x fsusb
```

Use it to flash bootloader
```
./fsusb --program ./something.hex
```

You may reset the chip afterwards:
```
./fsusb --reset
```

#### Switch to bootloader using my usb stack firmware:

```
sudo usb_modeswitch -v ffff -d 0100 -S
```
The command switches the usb stack on the target microchip, so the usb\_modeswitch reports a failure, but everything is ok.

### Flash new hex without bootloader

After compiling, flash new hex using ipecmd utility distributed with MPlabX Microchip.
Following example is for PICKIT3:
```
yaourt -S mplabx
cd /tmp
sudo /opt/microchip/mplabx/v*/mplab_ipe/ipecmd.sh -P18F2550 -TPPK3 -M -F./bootloader.hex
```

### Flash new bootloader

Compile bootloader with:

```
pacman -S sdcc
git clone https://github.com/Kamilcuk/PicUsbBootloader
pushd PicUsbBootloader/18f2550
make VID=04d8 PID=000b
popd
```
**or**
```
wget https://github.com/Kamilcuk/PicUsbBootloader/releases/download/0.1/pic18f2550_bootloader.hex
```

Flash generated hex using ipecmd utility:
```
yaourt -S mplabx
cd /tmp
sudo /opt/microchip/mplabx/v*/mplab_ipe/ipecmd.sh -P18F2550 -TPPK3 -M -F./bootloader.hex
```

# Add hwdb databse to udev

```
git clone https://github.com/Kamilcuk/pic_projects
cd pic_projects
sudo mkdir -p /etc/udev/hwdb.d
sudo install -o root -g root -m 0644 ./kamiltech.hwdb /etc/udev/hwdb.d/
sudo udevadm hwdb --update
```

# Author
Kamil Cukrowski <kamilcukrowski@g_m_a_i_l.com>

# License
See LICENSE file.
Copyright (C) by Kamil Cukrowski under MIT Expat License with added Beerware license clause.

Microchips usb pic18 stack mla_usb is under Apache license  
Boost is under Boost Software License  
Microchips peripheral library plib is under their license and can be used only with Microchip products  
The protothread library is copyright by Serge Zaitsev under MIT License  
The author of ds18b20 code is Martin Thomas <eversmith@heizung-thomas.de>  
Authors of onewire communication Martin Thomas (mthomas(at)rhrk.uni-kl.de) and Peter Dannegger (danni(at)specs.de)  

# Thanks to
To mom and dad!
All the works and code writters I could use. Thank You!
To Microchip for their chips and usb stack.

### Sry my bad English : )


