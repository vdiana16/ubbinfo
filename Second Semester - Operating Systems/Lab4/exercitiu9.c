#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	int c1toc2[2],c2toc1[2];
	if(pipe(c1toc2)==-1)
	{
		perror("pipe()");
		exit(1);
	}
	if(pipe(c2toc1)==-1)
	{
		perror("pipe()");
		exit(1);
	}
	int pid=fork();
	if(pid==-1)
	{
		perror("fork()");
	}
	if(pid==0)
	{
		close(c2toc1[1]);
		close(c1toc2[0]);
		int n;
		srandom(getpid());
		if(read(c2toc1[0],&n,sizeof(int))<0)
		{
			perror("Copilul1: Eroare");
		}
		printf("Copilul1 a citit %d\n", n);
		while(n!=10)
		{
			n=random()%10+1;
			if(write(c1toc2[1],&n,sizeof(int))<0)
			{
				perror("Copilul1: Eroare");
			}
			if(n==10){
				break;
			}
			if(read(c2toc1[0],&n,sizeof(int))<0)
			{
				perror("Copilul2: Eroare");
			}
			printf("Copilul1 a citit %d\n",n);
		}
		close(c2toc1[0]);
		close(c1toc2[1]);
		exit(0);
	}
	pid=fork();
	if(pid==-1)
        {
                perror("fork()");
        }
        if(pid==0)
        {
                close(c2toc1[0]);
                close(c1toc2[1]);
                int n=0;
                srandom(getpid());
                while(n!=10)
                {
                        n=random()%10+1;
                        if(write(c2toc1[1],&n,sizeof(int))<0)
                        {
                                perror("Copilul1: Eroare");
                        }
                        if(n==10){
                                break;
                        }
                        if(read(c1toc2[0],&n,sizeof(int))<0)
                        {
                                perror("Copilul2: Eroare");
                        }
                        printf("Copilul2 a citit %d\n",n);
                }
                close(c2toc1[1]);
                close(c1toc2[0]);
                exit(0);
        }
	wait(0);
	wait(0);
	return 0;
}
