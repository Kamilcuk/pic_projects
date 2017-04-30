#!/bin/bash

cd ./.obj
f=main.as
fun=inline_main_inline

getFuncbody() {
	( echo "_${fun}:"; awk "/^_${fun}:$/{flag=1;next}/return/{flag=0}flag" $f ) | \
		sed -e '/^;/d' -e '/^\s\+line\s\+[0-9]\+$/d' -e '/^\s\+opt\s\+stack\s\+[0-9]\+$/d' -e '/^\s*$/d'
}
prepare_rename_labels() {
	sed -e 's/^\([_0-9a-zA-Z]\+\):$/\1_LABEL_:/' -e 's/goto[\t\s]\+\([_0-9a-zA-Z]\+\)/goto \1_LABEL_/'
}

funcbody=$(getFuncbody | prepare_rename_labels)

num=0
while IFS='\n' read -r line; do
	if echo "$line" | egrep -q '^[[:space:]]+call[[:space:]]+_'"$fun"'[[:space:]].*$'; then
		echo "; call '$fun' ; inlined function by $(basename $0)"
		echo "${funcbody}" | sed 's/_LABEL_/_'$num'_/'
		num=$((num+1))
	else
		echo "$line"
	fi
done <<< "$( cat "$f" | grep -A20 _inline_ )"  | sponge > main_optimized.as

