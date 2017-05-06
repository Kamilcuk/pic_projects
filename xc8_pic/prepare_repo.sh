#!/bin/bash

DIR=$(readlink $(basename $(readlink $0)))
cd $DIR
./plib_download_and_patch.sh
./patch_mla_usb.sh

