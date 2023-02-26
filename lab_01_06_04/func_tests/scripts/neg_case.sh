#!/bin/bash
touch waste.txt
if [ $# -eq 3 ]; then
	args=$(cat "$3")
	if [ -z "$USE_VALGRIND" ]; then
		(../../app.exe "$args" < "$1" > waste.txt)
	else
		(valgrind -q ~/task_1/app.exe "$args" < "$1" > waste.txt)
	fi
else
	if [ -z "$USE_VALGRIND" ]; then
		(../../app.exe < "$1" > waste.txt)
	else
		(valgrind -q ../../app.exe < "$1" > waste.txt)
	fi
fi

if [ $? -eq 1 ]
then
	exit 0 # test passed
else
	exit 1
fi
