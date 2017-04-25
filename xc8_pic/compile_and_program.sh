#!/bin/bash
make -j 4 -C 02_ultifan/ && ./program_fsusb.sh 02_ultifan/dist/default/production/02_ultifan.production.hex


