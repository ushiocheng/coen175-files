#!/bin/zsh

if [ -z $1 ]; then
    # printf "\x1b[33;41m[ERROR]\x1b[0m Usage: $0 <path-to-coen175-workspace>\n"
    # exit 1
    cd ..
    printf "\x1b[103;30m[WARN]\x1b[0m Inferring workspace base dir => $(pwd)\n"
else
    cd $1
fi

basedir=$(pwd)

if [ -e $basedir/phase6-mystuff/ ]; then
    cd $basedir/phase6
    printf "\x1b[102;30m[INFO]\x1b[0m working in $(pwd)\n"
else
    printf "\x1b[33;41m[ERROR]\x1b[0m Working Dir does not exist\n"
    exit 1
fi

printf "\x1b[102;30m[INFO]\x1b[0m Building phase6\n"
make clean
make

cd $basedir/phase6-mystuff/
mkdir -p test-output
rm test-output/*
cd examples

for f in *.c; do
    if [[ ! "a-li.c" =~ ".*-lib\.c" ]]; then
        BASE=$(basename $f .c)
        printf "\x1b[102;30m[INFO]\x1b[0m Testing $BASE ... "
        ulimit -t 1
        ../../phase6/scc \
            <$BASE.c \
            >../test-output/$BASE.s \
            2>../test-output/$BASE.compile.err
        # Compile & Link with lib
        if [ -e $BASE-lib.c ]; then
            gcc ../test-output/$BASE.s $BASE-lib.c -o ../test-output/$BASE.o
        else
            gcc ../test-output/$BASE.s -o ../test-output/$BASE.o
        fi
        if [ -e $BASE.in ]; then
            ../test-output/$BASE.o \
                <$BASE.in \
                >../test-output/$BASE.runtime.out \
                2>../test-output/$BASE.runtime.err
        else
            ../test-output/$BASE.o \
                >../test-output/$BASE.runtime.out \
                2>../test-output/$BASE.runtime.err
        fi
        cmp -s ../test-output/$BASE.runtime.out $BASE.out 2>/dev/null &&
            printf "ok\n" ||
            (
                printf "failed\n"
                printf "\x1b[33;41m[ERROR]\x1b[0m Test case $BASE failed!\n"
                cp $BASE.out ../test-output/$BASE.runtime.out.expected
                diff $BASE.out ../test-output/$BASE.runtime.out >../test-output/$BASE.runtime.out.diff
            )
    fi
done

# !Make clean but not delete executable
cd $basedir/phase6
rm lexer.cpp
rm **/*.o
