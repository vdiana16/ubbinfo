#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "header.h"

int main(int argc, char* argv[])
{
	int fd_read=open(myfifo1,O_RDONLY);
	if(-1 == fd_read) {
   		perror("Error opening fifo 1 in A");
   		exit(1);
 	}
  	int fd_write = open(myfifo2, O_WRONLY);
  	if(-1 == fd_write) {
  		perror("Error opening fifo 2 in B");
   		close(fd_read);
 		exit(1);
 	}
 	srandom(getpid());
  	int nr = 0;
	while(nr!=10)
	{
		nr=random()%10+1;
		if(read(fd_read,&nr,sizeof(int))<0)
		{
			perror("Eroare la citire din A");
			break;
		}
		printf("B primeste: %d\n", nr);
		if(write(fd_write,&nr,sizeof(int))<0)
		{
			perror("Eroare la scriere in A");
			break;
		}
		printf("B trimite:%d\n",nr);
	}
	close(fd_read);
	close(fd_write);
	return 0;
}
