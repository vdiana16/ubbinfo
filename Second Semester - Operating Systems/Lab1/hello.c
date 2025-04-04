#include <stdio.h>
int main(int argc, char **argv)
{
	int i;
	printf( "%d\n", argc );
	for ( i=0;i< argv;i++)
	{
		printf( argv );
	}
	return 0;
}

    
