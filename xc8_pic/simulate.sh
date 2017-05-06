#!/bin/bash -ue

FILE=$(readlink -f ${1:-./.obj/main.elf})
tempfile=$(mktemp)
trap 'rm -f $tempfile' EXIT
echo '
Device PIC18F2550
Hwtool SIM
Set uart1io.uartioenabled true
Set uart1io.output window
Set oscillator.frequency 48000000
Set oscillator.frequencyunit None
Set oscillator.auxfrequency 48000000
Set oscillator.auxfrequencyunit None
Set oscillator.rcfrequency 48000000
Set oscillator.rcfrequencyunit None
Program "'"${FILE}"'"
Reset MCLR
Run
Wait 120000
Quit
' | tee $tempfile
set -x
mdb $tempfile
