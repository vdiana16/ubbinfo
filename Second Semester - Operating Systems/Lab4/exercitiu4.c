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
        for(int i=0;i<strlen(sir);i++)
		printf("%c",sir[i]);
	return 0;
}
