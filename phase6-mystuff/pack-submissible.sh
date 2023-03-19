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

if [ -e $basedir/phase6-mystuff ]; then
    cd $basedir
    printf "\x1b[102;30m[INFO]\x1b[0m working in $(pwd)\n"
else
    printf "\x1b[33;41m[ERROR]\x1b[0m Working Dir does not exist\n"
    exit 1
fi

printf "\x1b[102;30m[INFO]\x1b[0m Cleaning up workspace...\n"
cd $basedir/phase6 \
    && make clean \
    || printf "\x1b[33;41m[ERROR]\x1b[0m Working Dir does not exist\n"
cd $basedir

tar -cf phase6-mystuff/phase6.tar phase6 &&
    printf "\x1b[102;30m[INFO]\x1b[0m packed phase6-mystuff/phase6.tar\n" ||
    printf "\x1b[33;41m[ERROR]\x1b[0m Failed to pack phase6-mystuff/phase6.tar\n"

cd $basedir/phase6-mystuff/

tar -cf phase6-examples.tar examples &&
    printf "\x1b[102;30m[INFO]\x1b[0m packed phase6-mystuff/phase6-examples.tar\n" ||
    printf "\x1b[33;41m[ERROR]\x1b[0m Failed to pack phase6-mystuff/phase6-examples.tar\n"

printf "\x1b[102;30m[INFO]\x1b[0m calling checksub.sh\n"
sh checksub.sh phase6.tar phase6-examples.tar

printf "\x1b[102;30m[INFO]\x1b[0m Removing phase6-examples.tar\n"
rm phase6-examples.tar
