#!/bin/bash -ue

usage() {
	echo "USAGE: $0 <file in lst format|dir with lst file> [<function name>,...]"
}

p="${1:-.obj}"
if [ $# -gt 1 ]; then
	shift
	names="$@"
else
	usage
	echo "function name not given"
	exit 2
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


for n in $names; do
	for pre in "${prefunc_strings[@]}"; do
		cat "$file" | \
			sed -n "/^${prefunc_regex}${pre}${n}${postfunc_regex}$/,/^${prefunc_regex}${func_regex}${postfunc_regex}$/ p" | \
			cat ; # egrep "^${code_regex}" | head -n -1
	done
done

