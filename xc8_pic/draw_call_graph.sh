#!/bin/bash

usage() {
	echo "USAGE: $0 <file in lst format|dir with lst file> [<function name>,...]"
	exit
}

p="${1:-.obj}"
shift
names="$@"

if [ -d $p ]; then
	lstfiles=$(find $p -name '*.lst')
	if [ $(echo "$lstfiles" | wc -l) -ne 1 ]; then
		echo "	Warning: Found .lst files: "$lstfiles " - dunno wchich to choose, choosing first one."
	fi
	file="$(echo "$lstfiles" | head -n 1)"
	echo "	$p is a directory, but found .lst file named: $file"
fi
if [ ! -e $file ]; then
	usage
	echo "Error: $file not readable"
	exit
fi

codelinepre_regex='[ ]*[0-9]\+ '
prefunc_regex="${codelinepre_regex}"';; \*\*\*\*\*\*\*\*\*\*\*\*\*\*\* function '
funcpre_regex='\(i1\|i2\)\?_'
funcint_regex='[a-zA-Z0-9_]\+'
func_regex="${funcpre_regex}${funcint_regex}"
postfunc_regex=' \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*'
code_regex='[ ]*[0-9]+  [0-9A-F]{6}  [0-9A-F]{4}'
prefunc_strings=( "i1_" "i2_" "_" )

tempfile=/tmp/.mytempfile

if [ -z "$names" ]; then
	names="$(cat "$file" | sed "s/^${prefunc_regex}\(${func_regex}\)${postfunc_regex}$/\1/;tx;d;:x" | sort)"
	echo "	Discovered $(echo "$names"|wc -l) functions in $file"
fi

filebuff="$(cat "$file" | egrep '^[ ]*[0-9]+ ;;')"

echo "digraph G {" > $tempfile
for n in $names; do
	echo $n
	called="$(echo "$filebuff" | \
		sed -n "/^${prefunc_regex}${n}${postfunc_regex}$/,/^[ ]*[0-9]\+ ;; This function is called by:$/ p" | \
		sed -n '/^[ ]*[0-9]\+ ;; This function calls:$/,/^[ ]*[0-9]\+ ;; This function is called by:$/ p' | \
		egrep -v '^[ ]*[0-9]+ ;; This function ' | \
		sed -e 's/^[ ]*[0-9]\+ ;;\t\t\(.*\)/\1/' )"
	if [ -z "$called" ]; then
		echo "INTERNAL: ERROR"
		exit 1
	fi
	if [ "$(echo "$called"|wc -l)" -eq 1 ] && [ "$called" == "Nothing" ]; then
		continue;
	else
		echo "$called" | sed 's/^\(.*\)/\t'${n}' -> \1;/' | tee -a $tempfile
	fi
done

echo "}" >> $tempfile

set -x
rm -f $tempfile.png
dot $tempfile -Tpng -o $tempfile.png
xdg-open $tempfile.png

