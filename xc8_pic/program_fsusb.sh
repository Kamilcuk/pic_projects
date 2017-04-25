#!/bin/bash
if [ "$#" -lt 1 ] || [ ! -r "$1" ]; then
	echo "Error: file not given or not readable."
	exit 1
fi
( set -x; sudo usb_modeswitch -Q -v FFFF -p 0100 -S )
echo "while ! lsusb -d 04d8:000b; do :; done; sleep 0.1"
while ! lsusb -d 04d8:000b; do :; done; sleep 0.1
set -x
fsusb $1
fsusb --reset


