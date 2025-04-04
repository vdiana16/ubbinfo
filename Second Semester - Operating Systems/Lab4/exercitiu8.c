#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc,char* argv[])
{
	if(argc!=2)
	{
		printf("Nr insuficient de argumente!\n");
		exit(1);
	}
	int p2c[2],c2p[2];
	pipe(p2c);
	pipe(c2p);
	int pid=fork();
	if(pid==-1)
	{
		perror("fork()");
		exit(1);
	}
	if(pid==0)
	{
		close(p2c[1]);
		close(c2p[0]);
		int n=0,nr;
		float rez;
		if(read(p2c[0],&n,sizeof(int))<0)
		{
			perror("Eroare la citirea din parinte");
			close(p2c[0]);
			close(c2p[1]);
			exit(1);
		}
		for(int i=0;i<n;i++)
		{
			if(read(p2c[0],&nr,sizeof(int))<0)
			{
				perror("Eroare la citirea din parinte");
                       		close(p2c[0]);
                        	close(c2p[1]);
                 	        exit(1);
                	}
			rez+=nr;
		}
		rez/=n;
		if(write(c2p[1],&rez,sizeof(float))<0)
		{
			perror("Eroare la scrierea in copil");
			close(p2c[0]);
                        close(c2p[1]);
       	                exit(1);
                }
		close(p2c[0]);
                close(c2p[1]);
                exit(0);
	}
	else
	{
		close(p2c[0]);
		close(c2p[1]);
		int n=atoi(argv[1]);
		int nr;
		float rez=-1;
		//srandom(time(0));
		if(write(p2c[1],&n,sizeof(int))<0)
		{
			perror("Eroare la scriere in parinte");
			close(p2c[1]);
			close(c2p[0]);
			wait(0);
			exit(1);
		}
		for(int i=0;i<n;i++)
		{
			nr=random()%100;
			printf("Parintele a generat %d\n", nr);
			if(write(p2c[1],&nr,sizeof(nr))<0)
			{
				perror("Eroare la scriere in parinte");
				close(p2c[1]);
				close(c2p[0]);
			}	
		}
		wait(0);
		if(read(c2p[0],&rez,sizeof(float))<0)
		{
			perror("Eroare la rezultatul din child");
		}
		printf("Media %f\n",rez);
		close(p2c[1]);
		close(c2p[0]);
	}
	return 0;
}
