#!/bin/bash

gcc -std=c99 -Wall -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Werror -Wvla --coverage -O0 -c main.c 
gcc -std=c99 -Wall -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Werror -Wvla --coverage -O0 -c prints.c
gcc -std=c99 -Wall -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Werror -Wvla --coverage -O0 -c process.c
gcc -o app.exe main.o prints.o process.o --coverage -O0 -lm
