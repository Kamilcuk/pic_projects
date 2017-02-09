#!/bin/bash -eu

inputhex=${1}
output=""
line=""
temp=""

if [ ! -f "$inputhex" ]; then
	echo "$inputhex does not exists."
	exit 1
fi

calcControlSum() {
	local record=${1}
	local tosum=$(echo $record | sed -e 's/^://' -e 's/\(..\)/16#\1 + /g' -e 's/+ $//')
	eval printf "%X" "$(( 16#01 + ~( ${tosum} ) ))" | sed 's/.*\(..$\)/\1/'
}

num=1
while read line; do
	temp="$line"
	case "$num" in
	2|3|4) # sdcc writes interrupts to hex file to 2nd, 3rd and 4th lines.
		temp="$(echo "$temp" | sed -e 's/^\(:...\)0/\18/' -e 's/..$//')"
		temp="${temp}$(calcControlSum "${temp}")"
		echo "Changed vector location '$line' -> '$temp'"
		;;
	esac
	output+="$temp
"
	num=$((num+1))
done <<< "$(cat $inputhex)"

echo -n "$output" > "$inputhex"

