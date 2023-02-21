int f();

int main() {
    int* a = &f; /* This should give E3, expect lvalue */
}


