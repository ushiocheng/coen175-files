int main(void)
{
    int x, y, z;

    {
	long x, y, z;

	{
	    void *x, *y[10], z;		/* 'z' has type void */
	}
    }
}
