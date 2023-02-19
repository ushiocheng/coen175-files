long a, b;

void foo(int a, int b)
{
    int x, x;			/* redeclaration of 'x' */
}

long a, b;

void bar(void *b, void *b)	/* redeclaration of 'b' */
{
    int x;
    int *y, y;			/* redeclaration of 'y' */
}
