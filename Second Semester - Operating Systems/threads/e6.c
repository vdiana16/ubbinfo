#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>
#include <limits.h>

#define MAX_THR 50
#define MAX_NUM 100000

int numere[MAX_NUM];
int minim[MAX_THR];

pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;

void* do_work(void* arg)
{
	int id=*(int*)arg;
	free(arg);

	int min=INT_MAX;
	int st=id*(MAX_NUM/MAX_THR);
	int dr=st+MAX_NUM/MAX_THR;
	for(int i=st;i<dr;i++)
	{
		if(numere[i]<min)
			min=numere[i];
	}
	pthread_mutex_lock(&mtx);
	printf("Sunt threadul %d minim:%d\n",id,min);
	minim[id]=min;
	pthread_mutex_unlock(&mtx);
	return NULL;
}

int main(int argc,char* argv[])
{
	int fd=open("random-file",O_RDONLY);
	if(fd==-1)
	{
		perror("open()");
		exit(1);
	}
	for(int i=0;i<MAX_NUM;i++)
	{
		read(fd,&numere[i],2);
	}
	pthread_t tid[MAX_THR];
	for(int i=0;i<MAX_THR;i++)
	{
		int *p=(int *)malloc(sizeof(int));
		*p=i;
		pthread_create(&tid[i],NULL,do_work,p);
	}
	for(int i=0;i<MAX_THR;i++)
        {
                pthread_join(tid[i],NULL);
        }
	int min=INT_MAX;
	for(int i=0;i<MAX_THR;i++)
	{
		if(minim[i]<min)
			min=minim[i];
	}
	printf("Minim: %d\n",min);
	close(fd);
	return 0;
}
