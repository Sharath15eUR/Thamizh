#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Invalid arguments for the script."
	exit 1
fi

inp=$1

op="op.txt"
>"$op"

while IFS= read -r line; do
	if [[ "$line" =~ '"frame.time":' ]]; then
		echo "$line" >> "$op"
	fi

	if [[ "$line" =~ '"wlan.fc.type":' ]]; then
		echo "$line" >> "$op"
	fi
	
	if [[ "$line" =~ '"wlan.fc.subtype":' ]]; then
		echo "$line" >> "$op"
	fi

done < "$inp"
