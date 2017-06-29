#!/bin/bash
set -euo pipefail

if [ "$#" -lt 1 ] || [ ! -r "$1" ]; then
	echo "Error: file not given or not readable."
	exit 1
fi
( set -x; sudo usb_modeswitch -Q -v FFFF -p 0100 -S; )

echo "while ! lsusb -d 04d8:000b; do :; done; sleep 0.1; ( dmesg -wH )&"

exec 10< <(dmesg -wH)
timeout 0.1 cat <&10 >/dev/null || true
while ! lsusb -d 04d8:000b; do
	timeout 0.01 cat <&10 || true
done
exec 10>&-
sleep 0.1;

set -x
fsusb $1
fsusb --reset


