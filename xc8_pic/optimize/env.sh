#!/bin/bash

DIR=../.obj/
file=./main.as
outfile=./main_optimized.as

[ -f $file ] && chmod +w $file
cp -f "${DIR}/${file}" $file
chmod -w $file
