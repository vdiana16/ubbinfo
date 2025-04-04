#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int este_prim(int n)
{
	if(n<2)
		return 0;
	else
	{
		for(int d=2;d*d<=n;d++)
		{
			if(n%d==0)
			{
				return 0;
			}
		}
	}
	return 1;
}

int main(int argc,char* argv[])
{
	int pd[2];
	int rez=pipe(pd);
	if(rez==-1)
	{
		perror("pipe()");
		exit(EXIT_FAILURE);
	}
	int pid=fork();
	if(pid==-1)
	{
		perror("fork()");
		exit(EXIT_FAILURE);
	}
	if(pid==0)
	{
		close(pd[1]);
		int num;
		while(1)
		{
			read(pd[0],&num,sizeof(int));
			if(num==0)
				break;
			if(este_prim(num))
				printf("Numarul %d este prim",num);
			else
				printf("Numarul %d nu este prim",num);
			//sleep(2);
		}
		close(pd[0]);
		exit(EXIT_SUCCESS);
	}
	close(pd[0]);
	int num;
	while(1)
	{
		printf("Numarul:");
		scanf("%d",&num);
		write(pd[1],&num,sizeof(int));
		if(num==0)
			break;
	}
	close(pd[1]);
	//int status;
	//wait(&status);
	wait(NULL);
	return 0;
}
