#!/bin/bash
sizes=""
for ((i=200; i<=1000; i+=200)); do
	sizes=$sizes"$i "
done

percents=""
for ((i=0; i<=100; i+=10)); do
	percents=$percents"$i "
done


for size in $sizes; do
	for percent in $percents; do
		echo "3" > cmd_app.txt
		echo "$size $size" >> cmd_app.txt
		echo "$percent" >> cmd_app.txt
		echo "0" >> cmd_app.txt
		for ((i=0; i<50; i++)); do
			./app.exe < cmd_app.txt > /dev/null
			echo -n -e "| $i/50 | $size | $percent |\r"
		done
	done
done
