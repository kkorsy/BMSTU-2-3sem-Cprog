#!/bin/bash
gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -g -c main.c
gcc -g -o app.exe main.o -lm
