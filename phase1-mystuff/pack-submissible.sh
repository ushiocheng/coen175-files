#!/bin/sh

cd ~/coen175-files/
tar -cf examples.tar examples
tar -cf phase1.tar phase1
sh phase1-mystuff/checksub.sh phase1.tar examples.tar
rm examples.tar
