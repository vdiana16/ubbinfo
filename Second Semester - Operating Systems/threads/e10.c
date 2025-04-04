#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#include <limits.h>

#define MAX_THR 10
#define SIZE 3000
#define FULL 1
#define EMPTY 0

int C,N;
FILE* fd;
int buffer[SIZE+1];
int nr1;
int nr2;
int difabs=INT_MIN;
int stare=EMPTY;

pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t ci=PTHREAD_COND_INITIALIZER;
pthread_cond_t cp=PTHREAD_COND_INITIALIZER;

void* citire(void* arg)
{
	pthread_mutex_lock(&mtx);
	while(stare==FULL)
		pthread_cond_wait(&ci,&mtx);
	for(int i=0;i<SIZE;i++)
	{
		fscanf(fd,"%d",&buffer[i]);
	}
	stare=FULL;
	pthread_cond_broadcast(&cp);
	pthread_mutex_unlock(&mtx);
	return NULL;
}

void* procesare(void* arg)
{
	pthread_mutex_lock(&mtx);
	while(stare==EMPTY)
                pthread_cond_wait(&cp,&mtx);
	for(int i=0;i<SIZE-1;i++)
	{
		if(buffer[i]%10==C && buffer[i+1]%10==C)
		{
			int dif=abs(buffer[i]-buffer[i+1]);
			if(dif>difabs)
			{
				difabs=dif;
				nr1=buffer[i];
				nr2=buffer[i+1];
			}
		}
	}
	stare=EMPTY;
        pthread_cond_broadcast(&ci);
        pthread_mutex_unlock(&mtx);
        return NULL;
}

int main(int argc,char* argv[])
{
	printf("Dati n: ");
	scanf("%d",&N);
	printf("\n");
	printf("Dati c: ");
	scanf("%d",&C);
	printf("\n");
	fd=fopen("fis","r");
	if(fd==NULL)
	{
		perror("fopen()");
		exit(1);
	}
	pthread_t ctid[MAX_THR];
	pthread_t ptid[MAX_THR];
	for(int i=0;i<MAX_THR;i++)
	{
		pthread_create(&ctid[i],NULL,citire,NULL);
		pthread_create(&ptid[i],NULL,procesare,NULL);
	}
	for(int i=0;i<MAX_THR;i++)
        {
                pthread_join(ctid[i],NULL);
                pthread_join(ptid[i],NULL);
        }
	printf("Diferenta este: %d si numerele sunt: %d,%d\n",difabs,nr1,nr2);
	return 0;
}
