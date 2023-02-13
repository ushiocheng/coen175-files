#!/bin/sh

basedir='/Users/ushio/Documents/VSCode/coen175-files'

if [[ -e $basedir/phase3-mystuff/ ]]; then
    cd $basedir/phase3
    printf "\x1b[102;30m[INFO]\x1b[0m working in $(pwd)\n"
else
    printf "\x1b[33;41m[ERROR]\x1b[0m Working Dir does not exist\n"
    exit 1
fi

printf "\x1b[102;30m[INFO]\x1b[0m Building phase 3\n"
make clean
make

cd $basedir/phase3-mystuff/
mkdir -p test-output
rm test-output/*
cd examples

for f in *.c; do
    printf "\x1b[102;30m[INFO]\x1b[0m Testing $f ... "
    ulimit -t 1
    ../../phase3/scc \
        <$f \
        >../test-output/$f.out \
        2>../test-output/$f.err
    cmp -s ../test-output/$f.err $(basename $f .c).err 2>/dev/null &&
        printf "ok\n" ||
        (
            printf "failed\n"
            printf "\x1b[33;41m[ERROR]\x1b[0m Test case $f failed!\n"
            cp $(basename $f .c).err ../test-output/$f.err.expected
        )
done

# !Make clean but not delete executable
cd $basedir/phase3
rm lexer.cpp
rm **/*.o
