#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "header.h"

int main(int argc,char* argv[])
{
	if(mkfifo(myfifo1,0600)<0)
	{
		perror("Eroare fifo 1");
		exit(1);
	}
	if(mkfifo(myfifo2,0600)<0)
	{
		perror("Eroare fifo 2");
		exit(1);
	}
	int fd_write=open(myfifo1,O_WRONLY);
	if(fd_write==-1)
	{
		perror("Eroare deschidere fifo 1");
		exit(1);
	}
	int fd_read=open(myfifo2,O_RDONLY);
	if(fd_read==-1)
	{
		perror("Eroare deschidere fifo 2");
		close(fd_write);
		exit(1);
	}
	srandom(getpid());
	int nr=0;
	while(nr!=10)
	{
		nr=random()%10+1;
		if(write(fd_write,&nr,sizeof(int))<0)
		{
			perror("Eroare scriere in copil");
			break;
		}
		printf("Parintele trimite: %d\n",nr);
		if(read(fd_read,&nr,sizeof(int))<0)
		{
			perror("Eroare citire din copil");
			break;
		}
		printf("Parintele primeste: %d\n",nr);
	}
	close(fd_write);
	close(fd_read);
	if(unlink(myfifo1)<0)
	{
		perror("Eroare stergere fifo1");
	}
	if(unlink(myfifo2)<0)
	{
		perror("Eroare stergere fifo2");
	}
	return 0;
}
