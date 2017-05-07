#!/bin/bash -xue

DIR=$(readlink -f $(dirname $(readlink -f $0)))
cd $DIR
rm -f ../.obj/main_optimized*
cp main_optimized.as ../.obj/main_optimized.as
cd ../.obj
../xc8.sh --pass1 -o./main_optimized.hex ./main_optimized.as

