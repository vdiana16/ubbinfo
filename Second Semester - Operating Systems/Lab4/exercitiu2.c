#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	int n=20;
	for(int i=2;i<n/2;i++)
	{
		int pid=fork();
		if(pid==-1)
		{
			perror("fork()");
			exit(EXIT_FAILURE);
		}
		if(pid==0)
		{
			FILE* fd=fopen("numere","r");
			if(fd==NULL)
			{
				perror("popen()");
				exit(EXIT_FAILURE);
			}
			int k=0;
			int num=0;
			int *numere=malloc(n*sizeof(int));
			while(fscanf(fd,"%d",&num)>0)
			{
				if((num%i)!=0 || num==i)
					numere[k++]=num;
			}
			fclose(fd);
			fd=fopen("numere","w");
			if(fd==NULL)
			{
				perror("popen()");
                                exit(EXIT_FAILURE);
			}
			for(int j=0;j<k;j++)
			{
				fprintf(fd,"%d",numere[j]);
			}
			fclose(fd);
			free(numere);
			exit(EXIT_SUCCESS);
		}
		wait(NULL);
	}
	return 0;
}
