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

if [ -e $basedir/phase4-mystuff ]; then
    cd $basedir
    printf "\x1b[102;30m[INFO]\x1b[0m working in $(pwd)\n"
else
    printf "\x1b[33;41m[ERROR]\x1b[0m Working Dir does not exist\n"
    exit 1
fi

printf "\x1b[102;30m[INFO]\x1b[0m Cleaning up workspace...\n"
cd $basedir/phase4 \
    && make clean \
    || printf "\x1b[33;41m[ERROR]\x1b[0m Working Dir does not exist\n"
cd $basedir

tar -cf phase4-mystuff/phase4.tar phase4 &&
    printf "\x1b[102;30m[INFO]\x1b[0m packed phase4-mystuff/phase4.tar\n" ||
    printf "\x1b[33;41m[ERROR]\x1b[0m Failed to pack phase4-mystuff/phase4.tar\n"

cd $basedir/phase4-mystuff/

tar -cf phase4-examples.tar examples &&
    printf "\x1b[102;30m[INFO]\x1b[0m packed phase4-mystuff/phase4-examples.tar\n" ||
    printf "\x1b[33;41m[ERROR]\x1b[0m Failed to pack phase4-mystuff/phase4-examples.tar\n"

printf "\x1b[102;30m[INFO]\x1b[0m calling checksub.sh\n"
sh checksub.sh phase4.tar phase4-examples.tar

printf "\x1b[102;30m[INFO]\x1b[0m Removing phase4-examples.tar\n"
rm phase4-examples.tar
