#!/bin/bash

HEX=${1}
start=$(cat $HEX | grep "^:10" | head -n1 | sed 's/^:10\([0-9a-fA-F]\{4\}\).*$/\1/')
stop=$(cat $HEX | grep "^:10" | tail -n1 | sed 's/^:10\([0-9a-fA-F]\{4\}\).*$/\1/')
length=$(( 0x${stop} - 0x${start} ))

printf "Hex file starts at $start, stops at $stop, has length of 0x%x=%d bytes\n" $length $length



