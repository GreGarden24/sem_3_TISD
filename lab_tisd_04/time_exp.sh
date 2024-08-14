#!/bin/bash
sizes=""
for ((i=2000; i<=10000; i+=2000)); do
	sizes=$sizes"$i "
done

for size in $sizes; do
	echo "5" > cmd_app.txt
	echo "$size" >> cmd_app.txt
	echo "0" >> cmd_app.txt
	for ((i=0; i<50; i++)); do
		./app.exe < cmd_app.txt > /dev/null
		echo -n -e "| $i/50 | $size |\r"
	done
done
