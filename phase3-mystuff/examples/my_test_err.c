int foo(), bar();

int foo( void ){
    /* int bar(); /* parsing error here */
    int bar;
}
int bar(void a) {} /* error E5 here */
