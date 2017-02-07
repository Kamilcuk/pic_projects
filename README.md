# pic_projects
My Microchip PIC18F2550 related projects

# Flash new pic with bootloader

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
**then**
```
yaourt -S mplabx
sudo /opt/microchip/mplabx/v*/mplab_ipe/ipecmd.sh -P18F2550 -TPPK3 -M -F./bootloader.hex
```

Utility for bootloader:
```
git clone https://github.com/Kamilcuk/pic-PICDEM-fsusb
cd pic-PICDEM-fsusb
make
```
**or**
```
wget https://github.com/Kamilcuk/pic-PICDEM-fsusb/releases/download/0.1/fsusb
```

# Author
Kamil Cukrowski <kamilcukrowski@g_m_a_i_l.com>

# License
GNU, See LICENSE file

There's a possibility, that I forgot to mention original author of some files.  
Please contact me then immediately!  

# Thanks to:
All the works and code writters I could use. Thank You!

# Sry my bad English : )


