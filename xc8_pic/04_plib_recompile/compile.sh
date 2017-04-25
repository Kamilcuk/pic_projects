#!/bin/bash -uex

debug() { echo "$(date +%FT%T): DEBUG: $@"; }

download_run_plib_installer() {
	if [ -e include/plib.h ]; then
		debug "plib installation found. Omitting installation."
		return
	fi
	debug "Downloading instaler"
	( set -x
        curl -L -o 'plib-installer.run' -C - http://www.microchip.com/mymicrochip/filehandler.aspx?ddocname=en574970
	)
        chmod +x './plib-installer.run'
	debug "Installing plib to $(pwd)"
	( set -x
	sudo ./plib-installer.run --prefix $(pwd) --mode unattended
	)
	sudo chown $(whoami) -R $(pwd)
}

mkdir -p builddir
pushd builddir
download_run_plib_installer
popd
make "SRC=$(find builddir/sources/ -type f -name '*.c')" "INCDIR=builddir/include/" -j4
if [ ! -e pic18-plib-htc-18f2550.lpp ]; then
	echo "Uooo, compilation not succesfulll :/  "
	exit 1
fi
echo "YAY! SUCCESS!"
sudo cp ./pic18-plib-htc-18f2550.lpp /opt/microchip/xc8/*/lib/

