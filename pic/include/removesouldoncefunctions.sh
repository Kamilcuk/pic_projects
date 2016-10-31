#!/bin/bash

# there is code in my files with 
# declaration fo functions that use
# __once 
# it is defined like $define __once inline static
# the whole thing is that sdcc leaves the soul of the inlined function in the code
# this script removes it

file=$1

# search for function declarations containint __once
rmf=( $(grep '__once'  *.c | grep '(' | awk '  {  print $NF; } ' | sed 's/(.*//' | tr '\n' ' ') )

echo rmf: ${rmf[*]}

remove_once_functions ()
{
	local line=''
	local func=''
	local i=0
	exec 7<$1
	IFS=
	while read -r line <&7; do 
		for func in ${rmf[*]}; do 
			if [[ "$line" = *"__$func"*"code"* ]]; then
				while read -r line <&7; do 
					if [[ "$line" = "; ; Starting pCode block"* ]]; then
						break;
					fi 
				done
			fi
		done
		echo -e "$line"
	done
}


remove_once_functions $file > /tmp/1


