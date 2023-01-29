#!/bin/sh

cd ~/coen175-files/
tar -cf p1-examples.tar phase1-mystuff/examples
tar -cf phase1.tar phase1
sh phase1-mystuff/checksub.sh phase1.tar p1-examples.tar
rm p1-examples.tar
