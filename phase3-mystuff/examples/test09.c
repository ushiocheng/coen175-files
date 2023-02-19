int a, foo();

int foo(void)
{
    a = z;			/* 'z' undeclared */
}

int foo();

char foo();			/* conflicting types for 'foo' */

int foo(void) {			/* redefinition of 'foo' */
}
