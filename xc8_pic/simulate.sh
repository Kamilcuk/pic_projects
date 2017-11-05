#!/bin/bash
set -ue

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

runUntilTextIsReceived() {
  local quittext="$1"
  shift
  ( PIDFILE=$(mktemp /tmp/foo.XXXXXX) && trap "rm -f $PIDFILE; wait;" 0 && {(
    set -x; "$@";
  ) > >( tee >( grep -q -x $quittext && kill $(cat $PIDFILE) ) ) &
  PID=$! && echo $PID >$PIDFILE ; wait $PID || true; })
}
runUntilTextIsReceived 'QUIT' mdb $tempfile
