#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_THR 10
#define MAX_SIZE 100
#define EMPTY 0
#define FULL 1

int buffer[MAX_SIZE];
int fd;
int sum=0;
int stare=EMPTY;

pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv=PTHREAD_COND_INITIALIZER;

void* producator(void* arg)
{
	pthread_mutex_lock(&mtx);
	while(stare==FULL)
	{
		//astept ca bufferul sa se goleasca
		pthread_cond_wait(&cv,&mtx);
	}
	for(int i=0;i<MAX_SIZE;i++)
	{
		read(fd,&buffer[i],2);
	}
	stare=FULL;
	pthread_cond_broadcast(&cv);
	pthread_mutex_unlock(&mtx);
	return NULL;
}

void* consumator(void* arg)
{
	pthread_mutex_lock(&mtx);
	while(stare==EMPTY)
		pthread_cond_wait(&cv,&mtx);
	for(int i=0;i<MAX_SIZE;i++)
	{
		sum+=buffer[i];
	}
	stare=EMPTY;
	pthread_cond_broadcast(&cv);
	pthread_mutex_unlock(&mtx);
	return NULL;
}

int main(int argc,char* argv[])
{
	fd=open("random-file",O_RDONLY);
	if(fd==-1)
	{
		perror("open()");
		exit(1);
	}

	pthread_t ctid[MAX_THR];
	pthread_t ptid[MAX_THR];
	for(int i=0;i<MAX_THR;i++)
	{
		pthread_create(&ctid[i],NULL,consumator,NULL);
		pthread_create(&ptid[i],NULL,producator,NULL);
	}
	for(int i=0;i<MAX_THR;i++)
        {
                pthread_join(ctid[i],NULL);
                pthread_join(ptid[i],NULL);
        }
	printf("SUMA:%d",sum);
	close(fd);
	return 0;
}
