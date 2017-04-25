#!/bin/bash -xue

cd "$(readlink -f "$(dirname "$(readlink -f $0)")")"

cp /opt/microchip/xc8/*/include/pic18f2550.h ./
files=(
	../include/mla_usb/src/{usb_device.c,usb_device_hid.c,usb_device_local.h}
	../include/mla_usb/inc/{usb.h,usb_device.h,usb_hal_pic18.h,usb_ch9.h}
)
cp "${files[@]}" ./
for i in *.h *.c; do
	sed -i -e 's/@\([^;]*\)\([;]\?\)/__at(\1)\2/g' $i
done

