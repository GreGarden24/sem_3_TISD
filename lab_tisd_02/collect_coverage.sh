#!/bin/bash

./build_gcov.sh
cd ./func_tests/scripts/ || exit 1
./func_tests.sh
cd ../../ || exit 1
gcov main.c
