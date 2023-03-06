#!/bin/sh

if [ -z $1 ]; then
    # printf "\x1b[33;41m[ERROR]\x1b[0m Usage: $0 <path-to-coen175-workspace>\n"
    # exit 1
    cd ..
    printf "\x1b[103;30m[WARN]\x1b[0m Inferring workspace base dir => $(pwd)\n"
else
    cd $1
fi

basedir=$(pwd)

if [ -e $basedir/phase5-mystuff/ ]; then
    cd $basedir/phase5
    printf "\x1b[102;30m[INFO]\x1b[0m working in $(pwd)\n"
else
    printf "\x1b[33;41m[ERROR]\x1b[0m Working Dir does not exist\n"
    exit 1
fi

printf "\x1b[102;30m[INFO]\x1b[0m Building phase5\n"
make clean
make

cd $basedir/phase5-mystuff/
mkdir -p test-output
rm test-output/*
cd examples

for f in *-lib.c; do
    BASE=$(basename $f -lib.c)
    printf "\x1b[102;30m[INFO]\x1b[0m Testing $BASE ... "
    ulimit -t 1
    ../../phase5/scc \
        <$BASE.c \
        >../test-output/$BASE.s \
        2>../test-output/$BASE.compile.err
    gcc ../test-output/$BASE.s $BASE-lib.c -o ../test-output/$BASE.o
    ../test-output/$BASE.o \
        > ../test-output/$BASE.runtime.out \
        2>../test-output/$BASE.runtime.err
    cmp -s ../test-output/$BASE.runtime.out $BASE.out 2>/dev/null &&
        printf "ok\n" ||
        (
            printf "failed\n"
            printf "\x1b[33;41m[ERROR]\x1b[0m Test case $BASE failed!\n"
            cp $BASE.out ../test-output/$BASE.runtime.out.expected
            diff $BASE.out ../test-output/$BASE.runtime.out > ../test-output/$BASE.runtime.out.diff
        )
done

# !Make clean but not delete executable
cd $basedir/phase5
rm lexer.cpp
rm **/*.o
