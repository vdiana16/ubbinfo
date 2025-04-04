    #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_SIZE 100



int main(int argc, char** argv)
{
	char sir[]="aeiouBAEIOUc";
	char vocale[]="aeiouAEIOU";
	for(int i=0;i<strlen(vocale);i++)
	{
		//descriptor pipe
		int pd[2];
		if(pipe(pd)<0)
		{
			perror("pipe");
			exit(1);
		}
		int pid=fork();
		if(pid<0)
		{
			perror("fork");
			exit(1);
		}
		if(pid==0)
		{
			//inchidem capatul care nu il folosim
			close(pd[0]);
			int k=0;
			char *tmp=malloc(MAX_SIZE*sizeof(char));
			//malloc poate esua
			for(int j=0;j<strlen(sir);j++)
			{
				if(sir[j]!=vocale[i])
				{
					tmp[k++]=sir[j];
				}
			}
			//atentie trebuie pus 0, nu e sigur ca va fi 0 in urma malloc
			tmp[k]='\0';
			//sau strlen(tmp)+1
			write(pd[1],tmp,MAX_SIZE);
			close(pd[1]);
			free(tmp);
			//termin copilul
			exit(0);
		}
		//parinte
		close(pd[1]);
		char *tmp=malloc(MAX_SIZE*sizeof(char));
		read(pd[0],tmp,MAX_SIZE);
		close(pd[0]);
		strcpy(sir,tmp);
		free(tmp);
		wait(NULL);
	}
	printf("Sir final:%s \n",sir);
	return 0;
}

    
