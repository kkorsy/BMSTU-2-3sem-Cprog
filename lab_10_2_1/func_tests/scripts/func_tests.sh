#!/bin/bash

# pos case
mapfile < <(find ../data -name "pos_*_in.txt") pos_files
num=${#pos_files[@]}
k="01"
passed_tests=0
failed_tests=0
memory_passed=0
memory_failed=0

for i in $(seq "$num"); do
	pos_in="pos_${k}_in.txt"
	pos_out="pos_${k}_out.txt"
	pos_args="../data/pos_${k}_args.txt"
	call="./pos_case.sh $pos_in $pos_out"

	if [ -f "$pos_args" ]; then
		call+=" $pos_args"
	fi
	
	$call
	code_return=$?

	case "$code_return" in
		0 ) 
			passed_tests=$((passed_tests + 1))
			memory_passed=$((memory_passed + 1));;
		1 )
			passed_tests=$((passed_tests + 1))
			memory_failed=$((memory_failed + 1));;
		2 )
			failed_tests=$((failed_tests + 1))
			memory_passed=$((memory_passed + 1));;
		3 )
			failed_tests=$((failed_tests + 1))
			memory_failed=$((memory_failed + 1));;
		4 ) passed_tests=$((passed_tests + 1));;
		5 ) failed_tests=$((failed_tests + 1));;
	esac

	if [ "$i" -ge 9 ]; then
		k="$((i + 1))"
	else
		k="0$((i + 1))"
	fi
done

echo "Positive tests: passed $passed_tests of $((failed_tests + passed_tests))"
if [[ -n "$USE_VALGRIND" ]]; then 
	echo "Memory tests: passed $memory_passed of $((failed_tests + passed_tests))"
fi
pos_failed_tests=failed_tests

# neg case
mapfile < <(find ../data -name "neg_*_in.txt") neg_files
num=${#neg_files[@]}
k="01"
passed_tests=0
failed_tests=0
memory_passed=0
memory_failed=0

for i in $(seq "$num"); do
	neg_in="../data/neg_${k}_in.txt"
	neg_args="../data/neg_${k}_args.txt"
	call="./neg_case.sh $neg_in"

	if [ -f "$neg_args" ]; then
		call+=" $neg_args"
	fi
	
	$call
	code_return=$?

	case "$code_return" in
		0 ) 
			passed_tests=$((passed_tests + 1))
			memory_passed=$((memory_passed + 1));;
		1 )
			passed_tests=$((passed_tests + 1))
			memory_failed=$((memory_failed + 1));;
		2 )
			failed_tests=$((failed_tests + 1))
			memory_passed=$((memory_passed + 1));;
		3 )
			failed_tests=$((failed_tests + 1))
			memory_failed=$((memory_failed + 1));;
		4 ) passed_tests=$((passed_tests + 1));;
		5 ) failed_tests=$((failed_tests + 1));;
	esac

	if [ "$i" -ge 9 ]; then
		k="$((i + 1))"
	else
		k="0$((i + 1))"
	fi
done

echo "Negative tests: passed $passed_tests of $((failed_tests + passed_tests))"
if [[ -n "$USE_VALGRIND" ]]; then 
	echo "Memory tests: passed $memory_passed of $((failed_tests + passed_tests))"
fi
neg_failed_tests=failed_tests

exit $((pos_failed_tests + neg_failed_tests))
