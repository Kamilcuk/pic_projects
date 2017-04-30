#!/bin/bash -uex

####################################### config #####################################

plibdir=./plib_installation

####################################### function #####################################

cd $(readlink -f $(dirname $(readlink -f $0)))

debug() { echo "$(date +%FT%T): DEBUG: $@"; }

download_install_plib() {
	if [ -e ${1}/include/plib.h ]; then
		debug "plib installation found. Omitting installation."
		return
	fi
	mkdir -p ${1}
	pushd ${1} >/dev/null
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
	popd >/dev/null
}

# download_install_plib
download_install_plib ${plibdir}

# patch plib
pushd ${plibdir}/include/plib >/dev/null
PRE='s/^\(#define.*\('
POST='\)\)/\\\\ \1/'
sed -i.bak sw_spi.h -e "$PRE"'PIN\|MODE'"$POST"
sed -i.bak xlcd.h   -e "$PRE"'PIN\|TRIS\|DATA'"$POST"
popd >/dev/null

pushd ${plibdir}/sources/pic18 >/dev/null
find -name '*.c' | while read line; do
sed -i.bak $line -e 's/\(far\|ram\|rom\|const\)//'
done
popd >/dev/null


echo "YAY! SUCCESS!"

