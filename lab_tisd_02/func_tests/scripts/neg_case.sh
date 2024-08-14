#!/bin/bash

args=""
if [ "$#" -gt 1 ]; then
	args="../data/$2"
fi

if [ -n "$USE_VALGRIND" ]; then
	eval valgrind --leak-check=yes ../../app.exe "$args" < ../data/"$1" > program_output.txt
else
	eval ../../app.exe "$args" < ../data/"$1" > program_output.txt
fi

if ! grep -Eo "[0-9]+" program_output.txt; then
	exit 0
else
	exit 1
fi
