int f();

int main(void) {
    int* a;
    a = &f; /* This should give E3, expect lvalue */
    f(a);
    f(a,a); // this is totally fine
}

int f(int a) {
    f(a);
    f(-a);
    f(&a);  // incompatible param
    f(*a);  // deref not ptr, uni op
    f(a,a); // param error

    f('c');
    f=a;    // lval
    a=f;    // type imc
    a=f(a); // fine?
    a=f();  // param mismatch
    a=&f;   // lval
    {
        int a,b,c;
        int *d;
        f(&d);  // param
        *d=a;
        **d=b;  // uni op deref
        d[0]=b;
        d=&(d[0]);
    }
}

