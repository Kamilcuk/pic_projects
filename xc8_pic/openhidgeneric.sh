#!/bin/bash -eu

################## config ########################

DEBUG=${DEBUG:-false}
$DEBUG && set -x

################## get usb device to connect to ###################

gethidraws() {
	readlink -f /sys/class/hidraw/* | cut -d'/' -f9,11 | \
		grep ":${1^^}\." | sed 's;^.*/;/dev/;'
}

f="$(gethidraws ffff:0100 | head -n1)"
if [ -z "$f" ]; then
	echo "Error: no usb device found."
	exit
fi
if [ ! -e $f ]; then
	echo "Error $f: does no exists"
	exit
fi
if [[ ! -r $f || ! -w $f ]]; then
	echo "Error $f: permission denied"
	exit
fi
echo "Detected $f device file."
if [ ! -c "$f" ]; then
	echo "error $f is not a character special file."
	echo "do: ' sudo rm $f ' and reconnect the device"
	exit 1
fi

###################### open usb device ###########################

fdin=10 fdout=11
exec $fdin>$f $fdout<$f # open file for writing and reading
trap 'childs=$(pgrep -P $$ || true); [ -n "$childs" ] && kill $childs; wait;' EXIT
trap 'exit 1' SIGUSR1

echo "## Running reading thread from $f"
(
	trap 'kill -SIGUSR1 $$' EXIT
	set -x
	cat <&$fdin
) &

echo "## Writing to $f"
while IFS= read -r -N 1 -s str; do
	$DEBUG && echo "FIFO IN: $str" >&2
	echo -ne "\x01$str" >&$1
	sleep 0.01
done

