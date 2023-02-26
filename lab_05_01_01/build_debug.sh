#!/bin/bash
for file in *.c; do
    gcc -std=c99 -g -Wall -Werror -Wextra -Wpedantic -Wfloat-conversion -Wfloat-equal -c "$file"
done

call="gcc -lm -o app.exe"
for file in *.o; do
    call+=" $file"
done

$call
