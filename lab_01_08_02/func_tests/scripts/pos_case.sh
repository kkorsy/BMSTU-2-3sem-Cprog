#!/bin/bash
touch file_stream_out.txt

if [ $# -eq 3 ]; then
	args=$(cat "$3")
	if [ -z "$USE_VALGRIND" ]; then
		( ../../app.exe "$args" < "$1" > file_stream_out.txt )
	else
		(valgrind -q ../../app.exe "$args" < "$1" > file_stream_out.txt)
	fi
else
	if [ -z "$USE_VALGRIND" ]; then
		( ../../app.exe  < "$1" > file_stream_out.txt )
	else
		(valgrind -q ../../app.exe < "$1" > file_stream_out.txt)
	fi
fi



if [[ "$(./comparator_result.sh file_stream_out.txt "$2")" -eq 0 ]]; then
	exit 0
else
	exit 1
fi
