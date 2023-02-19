int x, *y, z;

int foo(void) {
    long **x, y, *z;
}

int foo(void) {			/* redefinition of 'foo' */
    int **x, *y, z;
}
