int f();
int foo();
int a, b, c;

int f(int a, int b, int c) { return a; }

int foo(void) { return 0; }
int foo(void) { return 0; } /* E1 redef */

void bar();
void* bar();   /* Expect E2 conflict type */
void bar(void a) { /* Expect E5 void */
    return a;
} 

void f1();
void f1(void) {}
void f1(int a) {}  /* E1 redef */
void f1(int a) {}  /* E1 redef */

void f2();
void* f2(void){} /* E2 conflict type */
void f2(void){}
void f2(void a){} /* E1 redef */
void* f2(void){} /* E1 redef */

int f3(void) {
    int a;
    long a; /* E2 conflict type */
    int a; /* E3 redeclaration */
    int d;
    int e[5],e[6]; /* E2 conflict type */
    int e[5]; /* E3 redeclaraion */
    a=a+a;
    b=c+d;
    {
        int d;
        int g;
        b=d+g;
    }
    b=c+g; /* E4 'g' undeclared */
    b=c+d;
    f2(f3());
}
