#!/bin/bash

mini_dir="$1"
files=$(grep -l '[^a-zA-Z1-9_]readline(' $mini_dir/**/*.c);
if [ $? -ne "0" ]; then
	echo "you are not using readline?"
	exit 1
fi
count=$(echo "$files" | wc -l)
echo "found $count files using readline"

echo "do you want to patch them to use get_next_line if not running interactively? Y/n"
read do_patch
case "$do_patch" in
	[Nn]* )
		echo "ok, then not"
		exit 1
	;;
esac

for file in $files; do
	echo "patching $file"
	patched=$(sed -E 's/([^[:alnum:]_])readline\(/\1!isatty(0) ? gnl(0) : readline(/g' "$file")
	patched=$(echo '#include <unistd.h>' | cat - <(echo "$patched"))
	patched=$(echo 'char	*gnl(int fd);' | cat - <(echo "$patched"))
	echo "$patched" | cat - > "$file"
done
echo "done patching"

files=$(grep -l '[^a-zA-Z1-9_]add_history(' $mini_dir/**/*.c);
if [ $? -ne "0" ]; then
	echo "you are not using readline?"
	exit
fi
count=$(echo "$files" | wc -l)
echo "found $count files using add_history"

echo "do you want to patch them to only use add_history if running interactively? Y/n"
read do_patch
case "$do_patch" in
	[Nn]* )
		echo "ok, then not"
	;;
esac

for file in $files; do
	echo "patching $file"
	patched=$(sed -E 's/([^[:alnum:]_])add_history\(/\1!isatty(0) ? 0 : add_history(/g' "$file")
	echo '#include <unistd.h>' | cat - <(echo "$patched") > "$file"
done

echo "copy get_next_line.c and patch Makefile"
cp get_next_line.c "$mini_dir"/
makefile=$(sed -E 's/(\$\(NAME\):.*)/\1\n\tcc get_next_line.c -c/' "$mini_dir"/Makefile | \
	sed -E 's/(\$\(CC\).*) \$\(OBJ/\1 get_next_line.o $(OBJ/' | \
	sed -E 's/(\$\(CC\).*) \$\^/\1 get_next_line.o $^/')
echo "$makefile" > "$mini_dir"/Makefile

echo "done patching"
