#!/bin/sh

cd ~/coen175-files/
tar -cf p2-examples.tar phase2-mystuff/examples
tar -cf phase2.tar phase2
sh phase2-mystuff/checksub.sh phase2.tar p2-examples.tar
rm p2-examples.tar
