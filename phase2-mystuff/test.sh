#!/bin/sh

if [[ -e ~/coen175-files/phase2-mystuff/ ]]; then
    cd ~/coen175-files/phase2
    printf "\x1b[102;30m[INFO]\x1b[0m working in $(pwd)\n"
else
    printf "\x1b[33;41m[ERROR]\x1b[0m Working Dir does not exist\n"
    exit 1
fi

printf "\x1b[102;30m[INFO]\x1b[0m Building phase 2\n"
make

cd ~/coen175-files/phase2-mystuff/
cd examples

for f in *.c; do
    printf "\x1b[102;30m[INFO]\x1b[0m Testing $FILE ... "
    ulimit -t 1
    ../../phase2/scc \
        <$f \
        >../test-output/$f.out \
        2>/dev/null
    cmp -s ../test-output/$f.out $(basename $f .c).out 2>/dev/null &&
        printf "ok\n" ||
        (
            printf "failed\n"
            printf "\x1b[33;41m[ERROR]\x1b[0m Test case $f failed!\n"
        )
done
