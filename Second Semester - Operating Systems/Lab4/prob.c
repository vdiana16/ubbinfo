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
                int n;
                //char cuvant[20]="\0";
                char numefis[20]="\0";
                read(fd[0],&n,sizeof(int));
                read(fd[0],numefis,sizeof(numefis));
                printf("N: %d\nFisier: %s\n",n,numefis);
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
                char linie[1000],continut[10000];
                while(fgets(linie,sizeof(linie),filed
                close(fd[1]);
                fclose(filed);
                wait(NULL);
        }
        return 0;
}
