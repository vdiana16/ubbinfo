#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUM 100000
#define MAX_THR 100

pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;

int numere[MAX_NUM];
int sum=0;

void* do_work(void* arg)
{
	int id=*(int*)arg;
	free(arg);
	int st=id*MAX_NUM/MAX_THR;
	int dr=st+MAX_NUM/MAX_THR;
	for(int i=st;i<dr;i++)
	{
		pthread_mutex_lock(&mtx);
		//printf("%d ",numere[i]);
		sum+=numere[i];
		pthread_mutex_unlock(&mtx);
	}
	return NULL;
}


int main(int argc,char* argv[])
{
	//generare 100000 de numere aleatoare
	srand(time(NULL));
	for(int i=0;i<MAX_NUM;i++)
	{
		numere[i]=rand()%10;
	}

	pthread_t tid[MAX_THR];
	for(int i=0;i<MAX_THR;i++)
	{
		int *id=malloc(sizeof(int));
		*id=i;
		pthread_create(&tid[i],NULL,do_work,id);
	}
	for(int i=0;i<MAX_THR;i++)
        {
		pthread_join(tid[i],NULL);
	}
	printf("Suma este: %d\n",sum);
	return 0;
}

