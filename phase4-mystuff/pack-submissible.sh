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

if [ -e $basedir/phase3-mystuff ]; then
    cd $basedir
    printf "\x1b[102;30m[INFO]\x1b[0m working in $(pwd)\n"
else
    printf "\x1b[33;41m[ERROR]\x1b[0m Working Dir does not exist\n"
    exit 1
fi

printf "\x1b[102;30m[INFO]\x1b[0m Cleaning up workspace...\n"
cd $basedir/phase3 \
    && make clean \
    || printf "\x1b[33;41m[ERROR]\x1b[0m Working Dir does not exist\n"
cd $basedir

tar -cf phase3-mystuff/phase3.tar phase3 &&
    printf "\x1b[102;30m[INFO]\x1b[0m packed phase3-mystuff/phase3.tar\n" ||
    printf "\x1b[33;41m[ERROR]\x1b[0m Failed to pack phase3-mystuff/phase3.tar\n"

cd $basedir/phase3-mystuff/

tar -cf p3-examples.tar examples &&
    printf "\x1b[102;30m[INFO]\x1b[0m packed phase3-mystuff/p3-examples.tar\n" ||
    printf "\x1b[33;41m[ERROR]\x1b[0m Failed to pack phase3-mystuff/p3-examples.tar\n"

printf "\x1b[102;30m[INFO]\x1b[0m calling checksub.sh\n"
sh checksub.sh phase3.tar p3-examples.tar

printf "\x1b[102;30m[INFO]\x1b[0m Removing p3-examples.tar\n"
rm p3-examples.tar
