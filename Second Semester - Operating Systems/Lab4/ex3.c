#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char**argv)
{
	char litere[]="abcdefghij";
	for(int i=0;i<strlen(litere);i++)
	{
		int pd=fork();
		if(pd<0)
		{
			perror("fork()");
			exit(1);
		}
		if(pd==0)
		{
			FILE *fd=fopen("text.txt","r");
			if(fd==NULL)
			{
				perror("fopen()");
				exit(1);
			}
			char ch;
			int aparitii = 0;
			while((ch=fgetc(fd))>0)
			{
				if(ch==litere[i])
				{
					aparitii++;
				}
			}
			printf("Litera curenta %c este: %d\n",litere[i], aparitii);
			exit(0);
		}
		wait(NULL);
	}
	return 0;
}
