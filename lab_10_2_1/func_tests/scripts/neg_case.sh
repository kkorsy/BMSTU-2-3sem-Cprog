#!/bin/bash
cmd="../../app.exe"

if [ $# -eq 3 ]; then
	args=$(cat "$3")
	cmd="$cmd $args"
fi

if [[ -n "$USE_VALGRIND" ]]; then
	cmd="valgrind --leak-check=full $cmd"
fi

$cmd < "$1" 1> waste.txt 2> error.txt
code_error=$?

if [[ -n "$USE_VALGRIND" ]]; then 
	if [[ "$code_error" -ne 0 ]]; then
		if [[ "$(grep -o "ERROR SUMMARY: [0-9]*" error.txt)" = "ERROR SUMMARY: 0" ]]; then
			exit 0 # тесты пройдены, ошибок по памяти нет
		else
			exit 1 # тесты пройдены, есть ошибки по памяти
		fi
	else
		if [[ "$(grep -o "ERROR SUMMARY: [0-9]*" error.txt)" = "ERROR SUMMARY: 0" ]]; then
			exit 2 # тесты не пройдены, ошибок по памяти нет
		else
			exit 3 # тесты не пройдены, есть ошибки по памяти
		fi
	fi
else
	if [[ "$code_error" -ne 0 ]]; then
		exit 4 # без валгринда, тесты пройдены
	else
		exit 5 # без валгринда тесты не пройдены
	fi
fi
