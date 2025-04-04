#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <math.h>

int main(int argc,char* argv[])
{
	int n=5;
	float s=10.4;
	float rez=fabs(s-(float)n);
	printf("%f",rez);
	return 0;
}
