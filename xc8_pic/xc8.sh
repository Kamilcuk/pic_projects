#!/bin/bash -ue
set -o pipefail

XC8=$(echo /opt/microchip/xc8/*/bin/xc8 | sort | tail -n 1)

XC8args=(
	"-DGIT_REV_PARSE_HEAD_SHORT=$(git rev-parse --short HEAD)"
)

filter_free_notice() {
	sed \
		-e '/^:: warning: (1273) Omniscient Code Generation not available in Free mode/d' \
		-e '/^XCLM: Failed to elevate privilege - is the XCLM binary setuid-root?/d' \
		-e '/^You have compiled in FREE mode./{N;N;N;N;d;}'
}

(
  set -x
  $XC8 \
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
    "${XC8args[@]}" \
    "$@"
) 2>&1 | filter_free_notice

