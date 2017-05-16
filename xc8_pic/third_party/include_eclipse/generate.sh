#!/bin/bash -xue

cd "$(readlink -f "$(dirname "$(readlink -f $0)")")"

files=(
	/opt/microchip/xc8/*/include/pic18f2550.h
	../../include/mla_usb/src/{usb_device.c,usb_device_hid.c,usb_device_local.h}
	../../include/mla_usb/inc/{usb.h,usb_device.h,usb_hal_pic18.h,usb_ch9.h}
)

# copy files here
cp "${files[@]}" ./
# for every C file
for i in *.h *.c; do
	# convert @ 0x48 to __at( 0x48 )
	sed -i -e 's/@\([^;]*\)\([;]\?\)/__at(\1)\2/g' $i
done

echo '
#define DETACHED_STATE 11
#define ATTACHED_STATE 11
#define POWERED_STATE 11
#define DEFAULT_STATE 11
#define ADR_PENDING_STATE 11
#define ADDRESS_STATE 11
#define CONFIGURED_STATE 11
#define EVENT_CONFIGURED 11
#define EVENT_SET_DESCRIPTOR, 11
#define EVENT_EP0_REQUEST 11
#define EVENT_ATTACH 11
#define EVENT_TRANSFER_TERMINATED 11
' >> usb_device.h

