#!/bin/bash

test1=("a b c" "[LEAF: a b c]")
test2=("(echo a)" "(: [LEAF: echo a])")
test21=("(a && b)" "(: [&&: [LEAF: a] [LEAF: b]])")
test22=("(a && b || c)" "(: [||: [&&: [LEAF: a] [LEAF: b]] [LEAF: c]])")
test3=("(a && b) || (x && y)" "[||: (: [&&: [LEAF: a] [LEAF: b]]) (: [&&: [LEAF: x] [LEAF: y]])]")
test4=("a | b | c" "[|: [LEAF: a] [LEAF: b] [LEAF: c]]")
test5=("a && b | c" "[&&: [LEAF: a] [|: [LEAF: b] [LEAF: c]]]")
test51=("(a && b | c)" "(: [&&: [LEAF: a] [|: [LEAF: b] [LEAF: c]]])")
test6=("(a && b) || (x && y) | p" "[||: (: [&&: [LEAF: a] [LEAF: b]]) [|: (: [&&: [LEAF: x] [LEAF: y]]) [LEAF: p]]]")
test7=("a | b && x | y" "[&&: [|: [LEAF: a] [LEAF: b]] [|: [LEAF: x] [LEAF: y]]]")
test71=("(a | b) && (x | y)" "[&&: (: [|: [LEAF: a] [LEAF: b]]) (: [|: [LEAF: x] [LEAF: y]])]")
test72=("a | (b && x) | y" "[|: [LEAF: a] (: [&&: [LEAF: b] [LEAF: x]]) [LEAF: y]]")
test8=("((echo a))" "(: (: [LEAF: echo a]))")
test80=("((((echo a))))" "(: (: (: (: [LEAF: echo a]))))")
test81=("((echo a) && b)" "(: [&&: (: [LEAF: echo a]) [LEAF: b]])")
test82=("(b && (echo a))" "(: [&&: [LEAF: b] (: [LEAF: echo a])])")
test83=("(b && (echo a) && c)" "(: [&&: [&&: [LEAF: b] (: [LEAF: echo a])] [LEAF: c]])")

tests=(
	test1[@]
	test2[@]
	test21[@]
	test22[@]
	test3[@]
	test4[@]
	test5[@]
	test51[@]
	test6[@]
	test7[@]
	test71[@]
	test8[@]
	test80[@]
	test81[@]
	test82[@]
	test83[@]
)

for tst in "${tests[@]}"; do
	echo -n "> ${!tst:0:1}; "
	out=$(echo "${!tst:0:1}" | ../minishell)
	if [ "$out" != "${!tst:1:1}" ]; then
		echo -e "\033[1;31mERROR\033[0m"
		echo "$out"
	else
		echo -e "\033[1;32mOK\033[0m";
	fi
done
