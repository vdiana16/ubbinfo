#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 100

int main(int argc,char* argv[])
{
	char* sir=malloc(MAX_SIZE*sizeof(char));
	FILE* fd=fopen("text.txt","r");
	fgets(sir,MAX_SIZE,fd);
	printf("%s",sir);
	for(char ch='a';ch<='z';ch++)
	{
		int pd[2];
		int rez=pipe(pd);
		if(rez<0)
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
			int contor=0;
			for(int i=0;i<strlen(sir);i++)
			{
				if(ch==sir[i] || toupper(ch)==sir[i])
					contor++;
			}
			write(pd[1],&contor,sizeof(int));
			close(pd[1]);
			exit(EXIT_SUCCESS);
		}
		close(pd[1]);
		int nrap;
		read(pd[0],&nrap,sizeof(int));
		//if(nrap!=0)
			printf("Nr aparitii al literei %c este %d\n", ch, nrap);
		close(pd[0]);
		wait(NULL);
	}
	return 0;
}
