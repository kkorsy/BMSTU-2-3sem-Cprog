#!/bin/bash

cd ../../out/

for file in ../src/*.c; do
    gcc -std=c99 -Wall -Werror -Wextra -Wpedantic -g --coverage -Wfloat-conversion -Wfloat-equal -c "$file"
done

call="gcc -lm --coverage -o app.exe"
for file in *.o; do
    call+=" ./out/$file"
done

cd ../
$call
cd ./func_tests/scripts/
./func_tests.sh
cd ../../out/

for file in *.gcda; do
    gcov -r "$file"
done
