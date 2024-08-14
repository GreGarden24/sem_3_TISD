#!/bin/bash

args=""
if [ "$#" -gt 1 ]; then
	args="$(cat ../data/$2)"
fi

if [ -n "$USE_VALGRIND" ]; then
	cd ../../
	eval valgrind --leak-check=yes ./app.exe "${args:0:31}" ./func_tests/scripts/program_output.txt "${args:64:2}"
else
	cd ../../
	eval ./app.exe "${args:0:31}" ./func_tests/scripts/program_output.txt "${args:64:2}"
fi

if [ "$(cat ./func_tests/scripts/program_output.txt)"  == "" ]; then
	exit 0
else
	exit 1
fi
