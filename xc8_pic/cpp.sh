#!/bin/bash
set -u
args=()
temp=$(getopt -q -o I: -- $(make print-CFLAGS | grep "set to" | cut -d'[' -f2 | sed -e 's/]$//') | sed 's/--$//')
temp=$(eval echo $temp)
args+=( $temp )
temp=$(echo /opt/microchip/xc8/*/include/ | sort -u | tail -n1)
args+=( -I$temp )
set -x
cpp "${args[@]}" "$@"

