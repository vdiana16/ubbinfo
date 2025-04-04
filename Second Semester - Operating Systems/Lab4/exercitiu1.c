#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_SIZE 100

int main(int argc, char* argv[])
{
	char vocale[]="aeiouAEIOU";
	char sir[]="aeioubAEIOUC";
	for(int i=0;i<strlen(vocale);i++)
	{
		int pd[2];
		if(pipe(pd)==-1)
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
			close(pd[0]);
			int k=0;
			char* tmp=malloc(MAX_SIZE*sizeof(char));
			if(tmp==NULL)
			{
				perror("malloc()");
				exit(EXIT_FAILURE);
			}
			for(int j=0;j<strlen(sir);j++)
			{
				if(sir[j]!=vocale[i])
					tmp[k++]=sir[j];
			}
			tmp[k]='\0';
			write(pd[1],tmp,MAX_SIZE);
			close(pd[1]);
			free(tmp);
			exit(EXIT_SUCCESS);
		}
		close(pd[1]);
		char *tmp = malloc(MAX_SIZE*sizeof(char));
		read(pd[0],tmp,MAX_SIZE);
		strcpy(sir,tmp);
		close(pd[0]);
		free(tmp);
		wait(NULL);
	}
	printf("Sir final: %s\n", sir);
	return 0;
}
