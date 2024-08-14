#!/bin/bash

gcc -std=c99 -Wall -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Werror -Wvla --coverage -O0 -c main.c 
gcc -std=c99 -Wall -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Werror -Wvla --coverage -O0 -c country_t.c
gcc -o app.exe main.o country_t.o --coverage -O0 -lm
