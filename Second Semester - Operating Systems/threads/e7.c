#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>
#include <math.h>
#include <unistd.h>

#define MAX_THR 50
#define MAX_NUM 100000

int minim[MAX_THR];
int numere[MAX_NUM];

pthread_barrier_t barr;

void* do_work(void* arg)
{
	int id=*(int *)arg;
	free(arg);

	int min=INT_MAX;
	int st=id*(MAX_NUM/MAX_THR);
	int dr=st+MAX_NUM/MAX_THR;
	for(int i=st;i<dr;i++)
	{
		if(numere[i]<min)
			min=numere[i];
	}

	minim[id]=min;
	pthread_barrier_wait(&barr);
	int sum=0;
	for(int i=0;i<MAX_THR;i++)
	{
		sum+=minim[i];
	}
	float med=sum/MAX_THR;

	float diff=fabs(med-min);

	printf("Thread %d, min %d, medie %f, diferenta %f\n",id,min,med,diff);
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

	pthread_barrier_init(&barr,NULL,MAX_THR);

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
	pthread_barrier_destroy(&barr);
	close(fd);
	return 0;
}
