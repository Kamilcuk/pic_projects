#!/bin/bash

#old
#while sleep 0.1; do
#	./openhidgeneric.sh
#done

while true; do
	./openhidgeneric.sh
	sleep 0.01
       	inotifywait --include '/dev/hidraw*' -e create /dev
	sleep 0.01
done

