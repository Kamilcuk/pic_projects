#!/bin/bash -ue
XC8=$(echo /opt/microchip/xc8/*/bin/xc8 | sort | tail -n 1)
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
  "$@"

