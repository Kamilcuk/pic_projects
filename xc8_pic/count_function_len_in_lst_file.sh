#!/bin/bash -ue

usage() {
	echo "USAGE: $0 <file in lst format|dir with lst file> [<function name>,...]"
}

p="${1:-.obj}"
if [ $# -gt 1 ]; then
	shift
	names="$@"
fi

if [ -d $p ]; then
	lstfiles=$(find $p -name '*.lst')
	if [ $(echo "$lstfiles" | wc -l) -ne 1 ]; then
		echo "	Warning: Found .lst files: "$lstfiles " - dunno wchich to choose, choosing first one."
	fi
	file="$(echo "$lstfiles" | head -n 1)"
	echo "	$p is a directory, but found .lst file named: $file"
fi
if [ ! -e "$file" ]; then
	usage
	echo "Error: $file not readable"
	exit 1
fi

codelinepre_regex='[ ]*[0-9]\+ '
prefunc_regex="${codelinepre_regex}"';; \*\*\*\*\*\*\*\*\*\*\*\*\*\*\* function '
funcpre_regex='\(i1\|i2\)\?_'
funcint_regex='[a-zA-Z0-9_]\+'
func_regex="${funcpre_regex}${funcint_regex}"
postfunc_regex=' \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*'
code_regex='[ ]*[0-9]+  [0-9A-F]{6}  [0-9A-F]{4}'
prefunc_strings=( "i1_" "i2_" "_" )

if [  -z ${names+x} ]; then
	names="$(cat "$file" | \
		sed "s/^${prefunc_regex}\(${funcint_regex}\)${postfunc_regex}$/\1/;tx;d;:x" | \
		sort
	)"
	echo "	Discovered $(echo "$names"|wc -l) functions in $file"
	prefunc_strings=( "" )
fi

formatlen="$(echo "$names"|wc -L)"
sum=0
for n in $names; do
	for pre in "${prefunc_strings[@]}"; do
		linesraw() { cat $file | sed -n "/^${prefunc_regex}${pre}${n}${postfunc_regex}$/,/^${prefunc_regex}${func_regex}${postfunc_regex}$/ p" | egrep "^${code_regex}"; }
		normallines=$( linesraw | wc -l)
		doublelines=$( linesraw | egrep "^${code_regex}  [0-9A-F]{4}" | wc -l)
		lines=$(( $normallines+$doublelines ))
		if [ "$lines" -ne 0 ]; then
			printf "Function %${formatlen}s has %3d lines.\n" "${pre}${n}" "$lines"
			sum=$(( sum+lines ))
		fi
	done
done
echo "	Sum of lines in functions is equal $sum."
echo "	$file has $(cat $file | egrep "^${code_regex}" | wc -l) lines of code."


