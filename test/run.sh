#!/bin/bash

echo "        _       _     _          _ _    _           _            
  /\/\ (_)_ __ (_)___| |__   ___| | |  | |_ ___ ___| |_ ___ _ __ 
 /    \| | '_ \| / __| '_ \ / _ \ | |  | __/ _ / __| __/ _ | '__|
/ /\/\ \ | | | | \__ \ | | |  __/ | |  | ||  __\__ | ||  __| |   
\/    \/_|_| |_|_|___/_| |_|\___|_|_|   \__\___|___/\__\___|_|   
                                                                 "
bonus=0
if [ "$1" = "b" ] || [ "$1" = "a" ]; then
	bonus=1
fi

out=$(make -C ..)
if [ "$?" != "0" ]; then
	echo "$out"
	echo -e "\033[1;31mCompilation failed!\033[0m"
	exit 1
fi

errcount=0
rm -rf diffs temp
mkdir diffs temp

handle_cmd() {
	cd temp
	echo "infile content" > infile
	echo "infile second line" >> infile
	touch readonly
	chmod -wx readonly
	eval "$2" > ../outfile 2> ../out_stderr
	cd ..
	rm -rf temp/*
	res="$?"
	mv outfile "$1" 2> /dev/null
	err=$(cat out_stderr | sed 's/[^:]\+: \(line [^:]\+: \)\?/[progname]: /')
	echo "" >> "$1"
	echo "======== stderr =======" >> "$1"
	echo "$err" >> "$1"
	echo "======== return =======" >> "$1"
	echo "return value: $res" >> "$1"
}

handle_diff() {
	diff="$3"
	diff --unified=100 expected found > diff.diff
	if [ -s diff.diff ]; then
		echo "diff of execution of:" > "$diff"
		echo "$1" >> "$diff"
		echo "$2" >> "$diff"
		cat diff.diff >> "$diff"
		errcount=$((errcount + 1))
		echo -e "\033[1;31mERROR\033[0m"
	else
		echo -e "\033[1;32mOK\033[0m"
	fi
	rm -f found expected out_stderr diff.diff
}

execute_file_tests() {
	filename=$1
	echo ""
	echo "==== $filename ===="
	while read line; do
		IFS='	'; array=($line); unset IFS;
		echo -n "${array[1]} "
		diff="diffs/${array[0]}.diff"
		CMD1="echo \"${array[1]//\"/\\\"}\" | tr ';' '\\n' | bash"
		CMD2="echo \"${array[1]//\"/\\\"}\" | tr ';' '\\n' | ../../minishell"
		touch expected
		handle_cmd "expected" "$CMD1"
		handle_cmd "found" "$CMD2"
		handle_diff "$CMD1" "$CMD2" "$diff"
	done < "$filename";
}

if [[ "$1" == /* ]]; then
	execute_file_tests "test_cases$1"
else
	for filename in $(find test_cases -type f -exec echo "{}" \;); do
		if [[ $filename == test_cases/bonus/* && $bonus -eq "0" ]]; then
			continue
		fi
		execute_file_tests "$filename"
	done
fi

rm -rf temp

echo ""
if [[ $errcount -eq 0 ]]; then
	echo -e "\033[1;32mALL OK!\033[0m"
	rmdir diffs
elif [[ $errcount -eq 1 ]]; then
	echo -e "\033[1;31mONE TEST FAILED!\033[0m"
	echo "diff has been written to ./diffs/"
else
	echo -e "\033[1;31m${errcount} TESTS FAILED!\033[0m"
	echo "diffs have been written to ./diffs/"
fi
