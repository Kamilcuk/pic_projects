#!/bin/bash
set -ueo pipefail

################################## functions ###############################

filter_free_notice() {
	grep --line-buffered --invert-match \
		-e '^:: warning: (1273) Omniscient Code Generation not available in Free mode' \
		-e '^XCLM: Failed to elevate privilege - is the XCLM binary setuid-root?' \
		-e '^You have compiled in FREE mode.' \
		-e '^Using Omniscient Code Generation that is available in PRO mode,' \
		-e '^you could have produced up to 60% smaller and 400% faster code.' \
		-e '^See http://www.microchip.com/MPLABXCcompilers for more information.' \
		-e '^$'
}


filter_const_warnings() {
	awk '{
	if ( $0 ~ /: warning: \(359\) / ) {
		warnline = $0
		getline
		line = $0

		arg1 = $0
		sub(/pointer to /, "", arg1)
		sub(/ -> .*/, "", arg1)

		arg2 = $0
		sub(/.* -> pointer to const /, "", arg2)

		if ( arg2 !~ arg1 ) {
			print warnline
			print line
		}
	} else {
		print
	}
}
'
}

filter_const_warnings_test() {
	echo "
some other line
02_ultifan/main.c:365: warning: (359) illegal conversion between pointer types
pointer to unsigned char -> pointer to const unsigned char
02_ultifan/main.c:538: warning: (359) illegal conversion between pointer types
pointer to unsigned char -> pointer to const unsigned char
02_ultifan/main.c:544: warning: (359) illegal conversion between pointer types
pointer to unsigned char -> pointer to const unsigned char
02_ultifan/main.c:562: warning: (359) illegal conversion between pointer types
pointer to unsigned char -> pointer to const unsigned char
02_ultifan/main.c:571: warning: (359) illegal conversion between pointer types
pointer to unsigned char -> pointer to const unsigned char
02_ultifan/main.c:577: warning: (359) illegal conversion between pointer types
pointer to unsigned char -> pointer to const unsigned char
02_ultifan/main.c:734: warning: (359) illegal conversion between pointer types
pointer to struct dupa -> pointer to const unsigned char
	" | filter_const_warnings
}

####################################### main ##############################

XC8=xc8
if ! which $XC8 >/dev/null 2>/dev/null; then
	XC8=$(echo /opt/microchip/xc8/*/bin/xc8 | sort | tail -n 1)
	if ! which $XC8 >/dev/null 2>/dev/null; then
		echo "ERROR: no xc8 compiler found" >&2;
		exit 1;
	fi
fi

XC8version=$(bc <<<"scale=0;$(xc8 | sed -n '/Version/s/.*: //p')*1000/1;")
XC8args=(
        "-DGIT_REV_PARSE_HEAD_SHORT=$(git rev-parse --short HEAD)"
)
if [ $XC8version -eq 1420 ]; then XC8args+=( --MSGDISABLE=373 ); fi


# filter outfile from parameters to display it in front
outfiles=()
for i in "$@"; do
	if echo "$i" | egrep -q "^-o" ; then
		outfiles+=( $i )
	else
		XC8args+=( $i )
	fi
done

(
  set -x
  $XC8 \
    ${outfiles[@]} \
    --chip=18F2550  \
    --double=24 --float=24 --emi=wordwrite  \
    --opt=default,+asm,+asmfile,+speed,-space,-debug  \
    --addrqual=require  \
    --mode=pro -P -N255 --asmlist \
    --summary=default,-psect,-class,+mem,-hex,-file  \
    --rom=default,-0-7FF  \
    --output=default,-inhx032  \
    --runtime=default,+clear,+init,+keep,-no_startup,+download,+config,+clib,-plib \
    --output=-mcof,+elf:multilocs  \
    --stack=compiled:auto:auto:auto \
    --PARSER=lean \
    --DEP=gcc \
    --warn=-3 \
    "--errformat=%f:%l: error: (%n) %s"  \
    "--warnformat=%f:%l: warning: (%n) %s"  \
    "--msgformat=%f:%l: note: (%n) %s" \
    -G \
    "${XC8args[@]}"
) 2>&1 | filter_free_notice | filter_const_warnings

