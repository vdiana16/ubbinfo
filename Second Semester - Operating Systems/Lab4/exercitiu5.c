#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
	int n,fd[2];
	int rez=pipe(fd);
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
		close(fd[1]);
		while(1)
		{
			read(fd[0],&n,sizeof(int));
			if(n==0)
			{
				break;
			}
			else
			{
				if(n%2==0)
					printf("C: %d este par\n",n);
				else
					printf("C: %d este impar\n",n);
			}
			sleep(2);
		}
		close(fd[0]);
		exit(EXIT_SUCCESS);
	}
	while(1)
	{
		close(fd[0]);
		printf("n:");
		scanf("%d",&n);
		write(fd[1],&n,sizeof(int));
		if(n==0)
			break;
		sleep(2);
	}
	//int status;
	wait(NULL);
	close(fd[1]);
	return 0;
}
