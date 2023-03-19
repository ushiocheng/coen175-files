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
    if [[ ! $f =~ ".*-lib\.c" ]]; then
        BASE=$(basename $f .c)
        printf "\x1b[102;30m[INFO]\x1b[0m Testing $BASE ... \t"
        ulimit -t 1
        ../../phase6/scc \
            <$BASE.c \
            >../test-output/$BASE.s \
            2>../test-output/$BASE.compile.err &&
            printf "Finished\n" ||
            printf "\x1b[103;30m[WARN]\x1b[0m Finished with Error\n"
    fi
done

# !Make clean but not delete executable
# cd $basedir/phase6
# rm lexer.cpp
# rm **/*.o
