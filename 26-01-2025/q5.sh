#!/bin/sh

for file in $(ls q*.sh); do
	lpr $file
done
exit 0
