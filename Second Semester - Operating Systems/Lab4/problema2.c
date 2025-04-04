#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>

int main(int argc,char* argv[])
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
		close(pd[1]);
		int n;
		char numefis[20]="\0";
		read(pd[0],&n,sizeof(int));
		read(pd[0],numefis,sizeof(numefis));
		printf("N: %d\nFisier: %s\n",n,numefis);
		char cuvant[20]="\0";
		int contor=0;
		while(read(pd[0],cuvant,sizeof(cuvant))>0)
		{
			bool ecuv=1;
			for(int i=0;i<strlen(cuvant);i++)
			{
				if(cuvant[i]>='0' && cuvant[i]<='9')
				{
					ecuv=0;
					break;
				}
			}
			if(ecuv==1 && strlen(cuvant)==n)
				contor++;
		}
		printf("Cuvinte cu %d litere: %d\n",n,contor);
		if(contor%2==0)
		{
			printf("Dati un cuvant de %d litere: ",n);
			char cuvant2[20]="\0";
			scanf("%s",cuvant2);
			FILE* fd=fopen(numefis,"r");
			char continut[10000],linie[100];
			while(fgets(linie,sizeof(linie),fd)!=NULL)
			{
				strcat(continut,linie);
			}
			fclose(fd);
			fd=fopen(numefis,"w");
			fprintf(fd,"%s ",cuvant2);
			fputs(continut,fd);
			fclose(fd);
		}
		close(pd[0]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		int n;
		char numefis[20];
		close(pd[0]);
		printf("N: ");
		scanf("%d",&n);
		printf("Fisier: ");
		scanf("%s",numefis);
		write(pd[1],&n,sizeof(int));
		write(pd[1],numefis,sizeof(numefis));
		FILE* fd=fopen(numefis,"r");
		char cuvant[20];
		while(fscanf(fd,"%s",cuvant)!=EOF)
		{
			write(pd[1],cuvant,sizeof(cuvant));
		}
		fclose(fd);
		close(pd[1]);
		wait(NULL);
	}
	return 0;
}
