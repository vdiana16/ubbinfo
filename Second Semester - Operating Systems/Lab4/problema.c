#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int fd[2];
	if(pipe(fd)==-1)
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
		//copil
		close(fd[1]);
		int n,contor=0;
		//char cuvant[20]="\0";
		char numefis[20]="\0";
		read(fd[0],&n,sizeof(int));
		read(fd[0],numefis,sizeof(numefis));
		printf("N: %d\nFisier: %s\n",n,numefis);
		char cuvant[20]="\0";
		while(read(fd[0],cuvant,sizeof(cuvant))>0)
		{
			//printf("%s\n",cuvant);
			if(strlen(cuvant)==n)
			{
				contor++;
			}
		}
		printf("Cuvinte cu %d litere: %d\n",n,contor);
		close(fd[0]);
		char cuvant2[20]="\0";
		if(contor%2==0)
		{
			printf("Dati un cuvant cu %d litere: ",n);
			scanf("%s",cuvant2);
			FILE* filed=fopen(numefis,"r");
			if(filed==NULL)
			{
				perror("fopen()");
				exit(EXIT_FAILURE);
			}
			char linie[1000],continut[10000];
			while(fgets(linie,sizeof(linie),filed)!=NULL)
			{
				strcat(continut,linie);
			}
			fclose(filed);
			filed=fopen(numefis,"w");
			fprintf(filed,"%s ",cuvant2);
			fputs(continut,filed);
			fclose(filed);
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[0]);
		int n;
		printf("N: ");
		scanf("%d",&n);
		char numefis[20];
		printf("Fisier: ");
		scanf("%s",numefis);
		getchar();
		FILE* filed=fopen(numefis,"r");
		if(filed==NULL)
		{
			perror("fopen()");
			exit(EXIT_FAILURE);
		}
		write(fd[1],&n,sizeof(int));
		write(fd[1],&numefis,strlen(numefis));
		char cuvant[20];
		while(fscanf(filed,"%s",cuvant)!=EOF)
		{
			write(fd[1],cuvant,sizeof(cuvant));
		}
		close(fd[1]);
		fclose(filed);
		wait(NULL);
	}
	return 0;
}
