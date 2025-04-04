#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc,char* argv[])
{
	if(argc!=2)
	{
		perror("argc()");
		exit(1);
	}
	int fd=open(argv[1],O_RDONLY);
	if(fd==-1)
	{
		perror("open()");
		exit(1);
	}
	int i,nr;
	for(i=1;i<=10;i++)
	{
		read(fd,&nr,2);
		printf("%d ",nr);
	}
	return 0;
}
