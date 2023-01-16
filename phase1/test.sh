cd ../examples

for f in *.c
do
../phase1/scc < $f > ../phase1/test-output/$f.out
done

echo "Testing fib"
diff fib.out ../phase1/test-output/fib.c.out
echo "Testing hello"
diff hello.out ../phase1/test-output/hello.c.out
echo "Testing list"
diff list.out ../phase1/test-output/list.c.out
echo "Testing malloc"
diff malloc.out ../phase1/test-output/malloc.c.out
echo "Testing sum"
diff sum.out ../phase1/test-output/sum.c.out
echo "Testing tricky"
diff tricky.out ../phase1/test-output/tricky.c.out