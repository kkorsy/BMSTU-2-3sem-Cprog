#!/bin/bash
cmd="../../app.exe"

if [ $# -eq 3 ]; then
	args=$(cat "$3")
	cmd="$cmd $args"
fi

if [[ -n "$USE_VALGRIND" ]]; then
	cmd="valgrind $cmd"
fi

case "$args" in
	sb* )
		$cmd 1> file_stream_out.txt 2> file_stream_error.txt
		./comparator.sh file_stream_out.txt "$2";;
	fb* ) 
		$cmd
		echo "$args" > test.txt
		file=$(grep -o '[0-9][0-9]_out.txt' test.txt)
		./comparator.sh "$file" "$2";;
	db* ) 
		echo "$args" > test.txt
		num=$(grep -o '[0-9][0-9]' test.txt)
		cp ../data/pos_"$num"_in.txt "$num"_out.txt
		$cmd
		./comparator.sh "$num"_out.txt "$2";;
esac

code_return=$?

if [[ -n "$USE_VALGRIND" ]]; then 
	if [[ "$code_return" -eq 0 ]]; then
		if [[ "$(grep -o "ERROR SUMMARY: [0-9]*" file_stream_error.txt)" = "ERROR SUMMARY: 0" ]]; then
			exit 1 # тесты пройдены, ошибок по памяти нет
		else
			exit 0 # тесты пройдены, есть ошибки по памяти
		fi
	else
		if [[ "$(grep -o "ERROR SUMMARY: [0-9]*" file_stream_error.txt)" = "ERROR SUMMARY: 0" ]]; then
			exit 2 # тесты не пройдены, ошибок по памяти нет
		else
			exit 3 # тесты не пройдены, есть ошибки по памяти
		fi
	fi
else
	if [[ "$code_return" -eq 0 ]]; then
		exit 4 # без валгринда, тесты пройдены
	else
		exit 5 # без валгринда, тесты не пройдены
	fi
fi
