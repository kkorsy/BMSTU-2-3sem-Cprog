#!/bin/bash
cmd="./app.exe"

if [ $# -eq 3 ]; then
	args=$(cat "$3")
	cmd="$cmd $args"
fi

if [[ -n "$USE_VALGRIND" ]]; then
	cmd="valgrind --leak-check=full $cmd"
fi

cd ../../
$cmd < ./func_tests/data/$1 1> ./func_tests/scripts/file_out.txt 2> ./func_tests/scripts/error.txt
./func_tests/scripts/comparator.sh ./func_tests/scripts/file_out.txt ./func_tests/data/$2
code_return=$?
cd ./func_tests/scripts/

if [[ -n "$USE_VALGRIND" ]]; then 
	if [[ "$code_return" -eq 0 ]]; then
	err_count="$(grep -o "ERROR SUMMARY: [0-9]*" error.txt)"
		if [[ "$err_count" == "ERROR SUMMARY: 0" ]]; then
			exit 0 # тесты пройдены, ошибок по памяти нет
		else
			exit 1 # тесты пройдены, есть ошибки по памяти
		fi
	else
		if [[ "$err_count" == "ERROR SUMMARY: 0" ]]; then
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
