#!/bin/bash
set -ueo pipefail

################## config ########################

DEBUG=${DEBUG:-false}
$DEBUG && set -x

################## get usb device to connect to ###################

gethidraws() {
	readlink -f /sys/class/hidraw/* | cut -d'/' -f9,11 | \
		grep ":${1^^}\." | sed 's;^.*/;/dev/;'
}

f="$(gethidraws ffff:0100 | head -n1)"
testerr() { if eval [ "$1" ]; then echo "ERROR: $2" >&2; exit 1; fi; }
testerr "! -n \"$f\"" "no usb device found"
testerr "! -e \"$f\"" "file $f does not exists"
testerr "! -r \"$f\"" "file $f is not readable"
testerr "! -w \"$f\"" "file $f is not writable"
testerr "! -c \"$f\"" "file $f is not a character special file"
echo "Detected $f character special file"

###################### open usb device ###########################

exec 10<>$f
trap 'exec 10<&-; [ -n "$(jobs -p)" ] && kill "$(jobs -p)" 2>/dev/null || true;' EXIT
trap 'exit 1' SIGUSR1

echo "Opened $f"
(
	trap 'exec 10<&-; kill -SIGUSR1 $$;' EXIT
	cat <&10;
) &

while IFS= read -r -N 1 -s str; do
	$DEBUG && echo "FIFO IN: $str" >&2
	echo -ne "\x01$str" >&10
	sleep 0.01
done

