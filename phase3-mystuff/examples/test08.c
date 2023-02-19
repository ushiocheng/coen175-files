int a, b(), c();
void b(), d();			/* conflicting types for 'b' */
int c(), d(), e();		/* conflicting types for 'd' */

int y[10];
int y[5];			/* conflicting types for 'y' */
int x;
int x[10];			/* conflicting types for 'x' */
