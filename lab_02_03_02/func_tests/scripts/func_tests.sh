#!/bin/bash
pos_in="../data/pos_01_in.txt"
pos_out="../data/pos_01_out.txt"
pos_args="../data/pos_01_args.txt"
k=1
pos_failed_tests=0
pos_passed_tests=0
memory_passed=0
memory_failed=0

while [ -f $pos_in ] 
do
	# Если файл с аргументами существует
	if [ -f $pos_args ]; then
		./pos_case.sh $pos_in $pos_out $pos_args
	else
		./pos_case.sh $pos_in $pos_out
	fi
	code_return=$?
	
	if [[ "$code_return" -eq 0 ]]; then
		pos_passed_tests=$((pos_passed_tests + 1))
		memory_passed=$((memory_passed + 1))

	elif [[ "$code_return" -eq 1 ]]; then
		pos_passed_tests=$((pos_passed_tests + 1))
		memory_failed=$((memory_failed + 1))

	elif [[ "$code_return" -eq 2 ]]; then
		pos_failed_tests=$((pos_failed_tests + 1))
		memory_passed=$((memory_passed + 1))

	elif [[ "$code_return" -eq 3 ]]; then
		pos_failed_tests=$((pos_failed_tests + 1))
		memory_failed=$((memory_failed + 1))

	elif [[ "$code_return" -eq 4 ]]; then
		pos_passed_tests=$((pos_passed_tests + 1))

	elif [[ "$code_return" -eq 5 ]]; then
		pos_failed_tests=$((pos_failed_tests + 1))
	fi
	
	# Если файлов больше 10
	if [ $k -ge 9 ]; then
		k="$((k + 1))"
	else
		k="0$((k + 1))"
	fi
	
	pos_in="../data/pos_$k\_in.txt"
	pos_out="../data/pos_$k\_out.txt"
done
echo "Positive tests: passed $pos_passed_tests of $((pos_failed_tests + pos_passed_tests))"
if [[ -n "$USE_VALGRIND" ]]; then 
	echo "Memory tests: passed $memory_passed of $((pos_failed_tests + pos_passed_tests))"
fi

neg_in="../data/neg_01_in.txt"
neg_args="../data/neg_01_args.txt"
k=1
neg_failed_tests=0
neg_passed_tests=0
memory_passed=0
memory_failed=0

while [ -f $neg_in ] 
do
	# Если файл с аргументами существует
	if [ -f $neg_args ]; then
		./neg_case.sh $neg_in $neg_args
	else
		./neg_case.sh $neg_in
	fi
	code_error=$?
	
	if [[ "$code_error" -eq 0 ]]; then
		neg_passed_tests=$((neg_passed_tests + 1))
		memory_passed=$((memory_passed + 1))

	elif [[ "$code_error" -eq 1 ]]; then
		neg_passed_tests=$((neg_passed_tests + 1))
		memory_failed=$((memory_failed + 1))

	elif [[ "$code_error" -eq 2 ]]; then
		neg_failed_tests=$((neg_failed_tests + 1))
		memory_passed=$((memory_passed + 1))

	elif [[ "$code_error" -eq 3 ]]; then
		neg_failed_tests=$((neg_failed_tests + 1))
		memory_failed=$((memory_failed + 1))

	elif [[ "$code_error" -eq 4 ]]; then
		neg_passed_tests=$((neg_passed_tests + 1))

	elif [[ "$code_error" -eq 5 ]]; then
		neg_failed_tests=$((neg_failed_tests + 1))
	fi
	
	# Если файлов больше 10
	if [ $k -ge 9 ]; then
		k="$((k + 1))"
	else
		k="0$((k + 1))"
	fi
	
	neg_in="../data/neg_$k\_in.txt"
done

echo "Negative tests: passed $neg_passed_tests of $((neg_failed_tests + neg_passed_tests))"
if [[ -n "$USE_VALGRIND" ]]; then 
	echo "Memory tests: passed $memory_passed of $((neg_failed_tests + neg_passed_tests))"
fi

exit $((pos_failed_tests + neg_failed_tests))

