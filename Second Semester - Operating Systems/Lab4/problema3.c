#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc,char* argv[])
{
	int p2c1[2],p2c2[2];
	if(pipe(p2c1)==-1)
	{
		perror("pipe()");
		exit(EXIT_FAILURE);
	}
	if(pipe(p2c2)==-1)
        {
                perror("pipe()");
                exit(EXIT_FAILURE);
        }
	int pid1=fork();
	if(pid1==-1)
	{
		perror("fork()");
		exit(EXIT_FAILURE);
	}
	if(pid1==0)
	{
		close(p2c1[1]);
		close(p2c2[1]);
		close(p2c2[0]);
		char cuvant[20]="\0";
		int lg=0;
		while(read(p2c1[0],cuvant,sizeof(cuvant))>0)
		{
			lg+=strlen(cuvant);
		}
		printf("Eu sunt procesul 1: %d\n",lg);
		close(p2c1[0]);
		exit(EXIT_SUCCESS);
	}
	int pid2=fork();
	if(pid2==-1)
        {
                perror("fork()");
                exit(EXIT_FAILURE);
        }
	if(pid2==0)
	{
		close(p2c1[1]);
                close(p2c2[1]);
                close(p2c1[0]);
		char cuvant[20]="\0";
		int lg=0;
                while(read(p2c2[0],cuvant,sizeof(cuvant))>0)
                {
                        lg+=strlen(cuvant);
                }
		printf("Eu sunt procesul 2 %d\n",lg);
                close(p2c2[0]);
		exit(EXIT_SUCCESS);
	}
	close(p2c1[0]);
	close(p2c2[0]);
	char cuvant[20];
	//char sir1[100];
	//char sir2[100];
	while(1)
	{
		printf("Cuvant: ");
		scanf("%s",cuvant);
		if(strcmp(cuvant,"stop")==0)
			break;
		if(strstr(cuvant,"oa"))
		{
			write(p2c1[1],cuvant,sizeof(cuvant));
			
		}
		else
		{
			write(p2c2[1],cuvant,sizeof(cuvant));
			
		}
	}
	close(p2c1[1]);
	close(p2c2[1]);
	waitpid(pid1,NULL,0);
	waitpid(pid2,NULL,0);
	return 0;
}
