#!/bin/bash

################## config ########################

DEBUG=${DEBUG:-false}
$DEBUG && set -x

################## get usb device to connect to ###################

gethidraws() {
	local productvendor=${1^^}
	for i in /sys/class/hidraw/*; do 
		if basename $(readlink -f $i/../../) | grep -q ":${productvendor}\."; then
		       echo -n "/dev/"; basename $i;
	        fi
	done
}

f="$(gethidraws ffff:0100)"
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

fifo=$(mktemp)
childs=""

rm -f $fifo
mkfifo $fifo

trap_SIGUSR1() {
	#echo Exitting because my child killed me. >&2;
	exit;
}
trap 'trap_SIGUSR1;' SIGUSR1
trap_EXIT() {
	$DEBUG && set -x;
	kill $childs 2>/dev/null;
	rm -f $fifo;
	wait;
}
trap 'trap_EXIT;' EXIT

echo "## Running writing thread $f"
writingThread() {
	$DEBUG && set -x
	trap_EXIT_write() {
		$DEBUG && set -x;
		echo "Exit writing thread";
		rm -f $fifo;
		kill -SIGUSR1 $$ 2>/dev/null;
	}
	trap 'trap_EXIT_write;' EXIT
	while IFS= read -r -N 1 -d '' -s str; do
		$DEBUG && echo "FIFO IN: $str"
		if [ -c "$f" ]; then
			echo -ne "\x01$str" >> "$f"
			sleep 0.01
		fi
	done < "$fifo"
}
( writingThread ) &
childs+=" $!"

echo "## Running reading thread $f"
readingThread() {
	$DEBUG && set -x
	trap_EXIT_read() {
		$DEBUG && set -x;
		echo "Exit reading thread";
		kill -SIGUSR1 $$ 2>/dev/null;
	}
	trap 'trap_EXIT_read;' EXIT
	( set -x; cat "$f"; )
}
( readingThread ) &
childs+=" $!"

while IFS= read -r -N 1 -d '' -s str; do
	echo -ne "$str" 
done >> "$fifo"

echo "## ERROR - END!"


