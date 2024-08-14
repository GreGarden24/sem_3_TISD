#!/bin/bash

gcc -std=c99 -Wall -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Werror -Wvla -O2 -c main.c 
gcc -std=c99 -Wall -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Werror -Wvla -O2 -c country_t.c
gcc -o app.exe main.o country_t.o -lm
