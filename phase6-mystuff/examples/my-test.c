int a, b, c;
int bar();

int foo(int a, int b, long c) {
    a = b;
    int* ap;
    ap = &a;
    bar(a, b, c);
}
