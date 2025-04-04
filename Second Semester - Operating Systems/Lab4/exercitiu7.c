#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int nr_aparitii(char ch,char sir[50])
{
	int contor=0;
	for(int i=0;i<strlen(sir);i++)
	{
		if(ch==sir[i])
			contor++;
	}
	return contor;
}

int main(int argc, char* argv[])
{
	int pd[2];
	int res = pipe(pd);
	if(res == -1)
	{
		perror("pipe()");
		exit(1);
	}

	int pid = fork();
	if(pid == -1)
	{
		perror("fork()");
		exit(1);
	}
	if(pid==0)
	{
		close(pd[1]);
		while(1)
		{
			char ch='\0';
			read(pd[0],&ch,sizeof(char));
			printf("Am citit %c\n",ch);
			char sir[50]="\0";
			read(pd[0],sir,sizeof(sir));
			printf("Am citit %s\n",sir);
			if(strcmp(sir,"stop")==0)
			{
				break;
			}
			printf("Nr ap: %d\n", nr_aparitii(ch,sir));
		}
		close(pd[0]);
		exit(EXIT_SUCCESS);
	}
	close(pd[0]);
	while(1)
	{
		char ch;
		char sir[50];
		printf("c: ");
		scanf("%c",&ch);
		write(pd[1],&ch,sizeof(char));
		sleep(2);
		getchar();
		printf("sir: ");
		scanf("%s",sir);
		write(pd[1],sir,sizeof(sir));
		if(strcmp(sir,"stop") == 0)
			break;
		getchar();
		sleep(2);
	}
	close(pd[1]);
	wait(NULL);
	return 0;
}
