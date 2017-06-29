#!/bin/bash

while true; do
	./openhidgeneric.sh
	sleep 0.1
       	inotifywait --include '/dev/hidraw*' -e create /dev
	sleep 0.1
done

