#!/bin/bash

fail_tests_pos=0
for test in $(find ../data/ -name "pos_*_in.txt" | sort); do
	test=${test:8}
	if ! ./pos_case.sh "${test}" "${test//in/out}";
	then
		fail_tests_pos=$((fail_tests_pos+1))
	fi
done


fail_tests_neg=0
for test in $(find ../data/ -name "neg_*_in.txt" | sort); do
	test=${test:8}
	
	if ! ./neg_case.sh "${test}";
	then
		fail_tests_neg=$((fail_tests_neg+1))
	fi
done

fail_tests=$((fail_tests_pos + fail_tests_neg))
if [ "$fail_tests" -ne "0" ]; then
	echo "Positive tests failed: ${fail_tests_pos}."
	echo "Negative tests failed: ${fail_tests_neg}."
	exit 1
else
	echo "ALL TESTS PASSED!"
	exit 0
fi
