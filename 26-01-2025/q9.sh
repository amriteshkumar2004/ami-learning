#!/bin/sh

echo "Is it morning? Please answer yes or no"
read timeofday

case "$timeofday" in
	yes | y | Yes | YES | Y ) echo "Good Morning";;
	n* | N* ) echo "Good Afternoon";;
	* ) echo "Sorry, answer not recognized";;
esac

exit 0
