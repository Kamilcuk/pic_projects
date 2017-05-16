#!/bin/bash -uex

####################################### config #####################################

plibdir=./third_party/plib_installation

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
pushd ${plibdir}

# patch includes - user defines!
{
	pushd include/plib >/dev/null
	PRE='s/^\(#define.*\('
	POST='\)\)/\\\\ \1/'
	sed -i.bak sw_spi.h -e "$PRE"'PIN\|MODE'"$POST"
	sed -i.bak xlcd.h   -e "$PRE"'PIN\|TRIS\|DATA'"$POST"
	popd >/dev/null
}

{
	# backup sources
	if [ ! -d sources.bak ]; then
		cp -a sources sources.bak
	fi
	# rsync backuped sources
	rsync -va --delete sources.bak/ sources/
}

{
	# patch sources
	pushd sources/pic18/plib >/dev/null

	# merge all C files into one, for faster compilation, less logs...
	for i in ./*; do
		# omit non directories
		if [ ! -d ${i} ]; then
	       	continue;
		fi
		# if there are any *.c files in the directory
		if ls ${i}/*.c 1>/dev/null 2>&1; then
			# print all files into one file
			cat ${i}/*.c > ${i}/$(basename ${i}).notc
			rm ${i}/*.c
			mv ${i}/$(basename ${i}).notc ${i}/$(basename ${i}).c
		fi
	done

	# C18 compiler to XC8
	find -name '*.c' | xargs -t -n1 sed -i -e 's/\(far\|ram\|rom\|const\)//'

	# plib/CCP/CCP.c:450: warning: (1262) object "Fake" lies outside available data space
	sed -i 'CCP/CCP.c' -e 's/\*(unsigned char \*)/\*(const unsigned char \*)/'

	# plib/i2c/i2c.c:2599: warning: (343) implicit return at end of non-void function
	sed -i 'i2c/i2c.c' -e '2599i \ \ return 0;'
	
	popd >/dev/null
}

popd >/dev/null

echo "YAY! SUCCESS!"

