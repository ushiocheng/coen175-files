mkdir -p test-1
rm test-1/*
cp ../phase2/* test-1/
cd test-1
make
cd ../../examples

for f in *.c
do
../phase2-mystuff/test-1/scc < $f > ../phase2-mystuff/test-output/$f.out
done

echo "Testing fib"
diff fib.out ../phase2-mystuff/test-output/fib.c.out
echo "Testing hello"
diff hello.out ../phase2-mystuff/test-output/hello.c.out
echo "Testing list"
diff list.out ../phase2-mystuff/test-output/list.c.out
echo "Testing malloc"
diff malloc.out ../phase2-mystuff/test-output/malloc.c.out
echo "Testing sum"
diff sum.out ../phase2-mystuff/test-output/sum.c.out
echo "Testing tricky"
diff tricky.out ../phase2-mystuff/test-output/tricky.c.out
echo "Testing fib_tricky"
diff fib_nasty.out ../phase2-mystuff/test-output/fib_nasty.c.out
echo "Testing my_stuff"
diff my_stuff.out ../phase2-mystuff/test-output/my_stuff.c.out

cd ../phase2-mystuff && rm -r test-1 && rm -r test-output
