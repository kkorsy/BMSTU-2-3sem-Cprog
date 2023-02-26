#!/bin/bash
file_stream_out="$(grep -o "[0-9].*$" "$1")"
file_stream_expect_out="$(grep -o "[0-9].*$" "$2")"

if [ "$file_stream_out" = "$file_stream_expect_out" ]
then
	exit 0
else
	exit 1
fi
