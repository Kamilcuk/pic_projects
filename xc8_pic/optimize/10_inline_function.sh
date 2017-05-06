#!/bin/bash

. env.sh

getFuncbody() {
	( echo "${1}:"; awk "/^${1}:$/{flag=1;next}/return/{flag=0}flag" "${2}" ) | \
		sed -e '/^;/d' -e '/^\s\+line\s\+[0-9]\+$/d' -e '/^\s\+opt\s\+stack\s\+[0-9]\+$/d' -e '/^\s*$/d'
}
prepare_rename_labels() {
	local inst label
	inst='goto\|BC\|BN\|BNC\|BNN\|BNOV\|BNZ\|BOV\|BRA\|BZ'
	inst="$(echo "$inst" | tr '[:upper:]' '[:lower:]')"'\|'"$(echo "$inst" | tr '[:lower:]' '[:upper:]')"
	label='[_0-9a-zA-Z]\+'
	sed \
		-e '/^\('"$label"'\):/s/\('"$label"'\):/\1_LABEL_:/' \
		-e '/^[[:space:]]\+\('"$inst"'\)[[:space:]]\+'"$label"'/s/\('"$inst"'\)\([[:space:]]\+\)\('"$label"'\)/\1\2\3_LABEL_/'
}
functions_to_inline() {
	local func
	cat "$file" | egrep ";; \*\*\*\*\*\*\*\*\*\*\*\*\*\*\* function|psect.*inline" | while IFS='\n' read -r line; do
		if echo "$line" | egrep -q ';; \*\*\*\*\*\*\*\*\*\*\*\*\*\*\* function'; then
			func=$(echo "$line" | sed 's/^;; \*\*\*\*\*\*\*\*\*\*\*\*\*\*\* function \(.*\) \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*.*/\1/')
		elif echo "$line" | egrep -q 'psect.*'; then
			echo $func
		fi
	done | sort | uniq
}
substitute_call_to_function_with_function_body() {
	num=0
	callreg='^[[:space:]]+call[[:space:]]+'"$fun"'[[:space:]]'
	callsed='^[[:space:]]\+call[[:space:]]\+'"$fun"'[[:space:]]'
	file=$(cat)
	while echo "$file" | egrep -q "$callreg"; do
		substitute="$(
			(
				echo '; ----------------- START call '"$fun"' ; inlined function by '"$(basename $0) with num=$num"
				echo "${funcbody}" | sed 's/_LABEL_/_'"$num"'_/'
				echo '; ----------------- STOP  call '"$fun"' ; inlined function by '"$(basename $0) with num=$num"
			) | awk 1 ORS='\\n' | sed 's/&/\\\&/g'
		)"
		file="$( echo "$file" | sed '0,/'"$callsed"'/s/'"$callsed"'/'"$substitute"'/' )"
		num=$((num+1))
	done
	echo "$file" | \
		egrep -v '^[[:space:]]*FNCALL[[:space:]]+[a-zA-Z_-]+,'"$fun" | \
		egrep -v '^[[:space:]]*FNCALL[[:space:]]+'"$fun"',[a-zA-Z_-]+'

}
remove_function_body() {
	local start
	funcbody=false
	awk \
'/^;; \*\*\*\*\*\*\*\*\*\*\*\*\*\*\* function '"$fun"' \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*/{f=1} /^[[:space:]]+__end_of'"${fun}"'/{f=0} !f'
}

remove_all_comments() {
	sed -i \
		-e 's/[;#].*$//' \
		-e '/^[[:space:]]\+line[[:space:]].*$/d' \
		-e '/^[[:space:]]\+file[[:space:]].*$/d' \
		-e '/^[[:space:]]\+$/d' \
		-e '/^$/d' \
		"${1}"
}

tempfile=$(mktemp)
trap 'rm -f $tempfile' EXIT
cp $file $tempfile

new="" funcbody=""
for fun in $(functions_to_inline); do
	echo "## Inlining function $fun"
	echo "## ## Getting $fun body"
	funcbody=$(getFuncbody "$fun" "$file" | prepare_rename_labels)
	echo "## ## Substituting all \"call $fun\" by function body"
	new="$( cat "$tempfile" | fun=$fun substitute_call_to_function_with_function_body )"
	echo "$new" > "$tempfile"
	echo "## ## Removing $fun function body"
	new="$( cat "$tempfile" | fun=$fun remove_function_body )"
	echo "$new" > "$tempfile"
done

echo "## Removing all comments"
remove_all_comments "$tempfile"

echo "# Copying tempfile to destination"
{
	set -x;
	cp "$tempfile" "$outfile"
}

exit
