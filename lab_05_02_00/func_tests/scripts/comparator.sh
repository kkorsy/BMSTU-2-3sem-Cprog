#!/bin/bash

diff -q -Z -b "$1" "$2" > file_diff.txt
if [[ -s file_diff.txt ]]; then
	exit 1
else
	exit 0
fi
