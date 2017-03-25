# pic_projects

My Microchip PIC18F2550 related projects.  
Folders:  

```
./xc8_pic          - folder with projects using xc8 compiler
./xc8_pic/*        - one folder per project
./xc8_pic/system.h - main project configuration. system.h must be in every project and contains configuration (assert, usb_config.h, pin connections, memory layout configuration, etc.). File system.h is included from microchip's usb stack, so such file must exist.
./xc8_pic/include  - include directory
./utils            - utilities used on the host side to communicate with pic projects
./kamiltech.hwdb   - udev database with usb vendor numbers

# deprecated:
./pic              - folder with projects using sdcc compiler (deprecated)
./pic/include      - include files for pic projects
./pic/scripts      - scripts used in pic projects makefile
./pic/*            - one folder per pic firmware
```

## Compile

Makefile, make.  
To compile projects under xc8_pic directory you need xc8 compiler.   
To compile projects undev pic directory you need sdcc compiler.  

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
Mostly GNU, as stated in LICENSE file.  
Unless stated differently in a particular file.  
Small files are under beerware, so at least I can hope to get some beers some day.  

There's a possibility, that I forgot to mention original author of some files.  
I try to, but I may forgot.  
Please contact me then immediately!  

# Thanks to
To mom and dad!
All the works and code writters I could use. Thank You!
To Microchip for their chips and usb stack.

### Sry my bad English : )


