#!/bin/bash

args=""
if [ "$#" -gt 2 ]; then
	args="$(cat ../data/$3)"
fi

if [ -n "$USE_VALGRIND" ]; then
	cd ../../
	eval valgrind --leak-check=yes ./app.exe "${args:0:31}" ./func_tests/scripts/program_output.txt "${args:64:2}"
	./func_tests/scripts/comparator.sh ./func_tests/data/"$2" ./func_tests/scripts/program_output.txt
else
	cd ../../
	eval ./app.exe "${args:0:31}" ./func_tests/scripts/program_output.txt "${args:64:2}"
	./func_tests/scripts/comparator.sh ./func_tests/data/"$2" ./func_tests/scripts/program_output.txt
fi

exit $?
