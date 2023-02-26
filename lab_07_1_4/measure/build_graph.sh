#!/bin/bash

gcc -Wall -Werror -Wextra -Wpedantic -o mysort.exe mysort.c 
gcc -Wall -Werror -Wextra -Wpedantic -o qsort.exe qsort.c

./mysort.exe
./qsort.exe

gnuplot graph.gpi -persist
