
int f(int a, void* b) {
    return a;
}

int main(void){
    int a;
    int *b;
    int **c;
    f(*a,c); // Arg0 Error; Arg1 mismatch
    f(*a); // Arg0 Error; Argc mismatch
    f(*a,b,c); // Arg0 Error; Argc mismatch
}

/*
    line 12: invalid arguments to called function
    line 13: invalid arguments to called function
    line 14: invalid arguments to called function
*/
