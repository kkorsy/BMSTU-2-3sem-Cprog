#!/bin/bash

diff -q -Z -b "$1" "$2" > ./func_tests/scripts/file_diff.txt
if [[ -s ./func_tests/scripts/file_diff.txt ]]; then
	exit 1
else
	exit 0
fi
