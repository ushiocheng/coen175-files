#!/bin/sh

cd ~/coen175-files/
printf "\x1b[102;30m[INFO]\x1b[0m working in $(pwd)\n"

tar -cf phase2-mystuff/p2-examples.tar phase2-mystuff/examples \
&& printf "\x1b[102;30m[INFO]\x1b[0m packed phase2-mystuff/p2-examples.tar\n" \
|| printf "\x1b[33;41m[ERROR]\x1b[0m Failed to pack phase2-mystuff/p2-examples.tar\n";

tar -cf phase2-mystuff/phase2.tar phase2 \
&& printf "\x1b[102;30m[INFO]\x1b[0m packed phase2-mystuff/phase2.tar\n" \
|| printf "\x1b[33;41m[ERROR]\x1b[0m Failed to pack phase2-mystuff/phase2.tar\n";

cd phase2-mystuff/
printf "\x1b[102;30m[INFO]\x1b[0m working in $(pwd)\n"

printf "\x1b[102;30m[INFO]\x1b[0m calling checksub.sh\n"
sh checksub.sh phase2.tar p2-examples.tar

printf "\x1b[102;30m[INFO]\x1b[0m Removing p2-examples.tar\n"
rm p2-examples.tar
