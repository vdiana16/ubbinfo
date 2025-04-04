#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char* argv[])
{
	int pid=fork();
	if(pid==-1)
	{
		perror("fork() error");
		exit(EXIT_FAILURE);
	}
	if(pid==0)
	{
		printf("[IN CHILD] My pid is %d and parent pid is %d\n",getpid(),getppid());
	}
	else
	{
		printf("[IN PARENT] My pid is %d and child pid is %d\n", getpid(), pid);
	}
	return 0;
}
