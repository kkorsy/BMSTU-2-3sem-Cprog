#!/bin/bash
gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wconversion -c main.c -lm
gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wconversion -o app.exe main.o -lm