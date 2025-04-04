    #include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <time.h>

#define MAX_THR 50
#define MAX_NUM 100000

int numere[MAX_NUM];
int suma_minime=0;
int minime[MAX_THR];

//bariera
pthread_barrier_t barr;

//se aloca static pentru mutex
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER; 

void* do_work(void* arg)
{
	//thread start routine
	int id=*(int*)arg; //aici transmitem i
	free(arg);
	int st=id*(MAX_NUM/MAX_THR);
	int dr=st+(MAX_NUM/MAX_THR);
	int min=INT_MAX;
	for(int i=st;i<dr;i++)
	{
		if(numere[i]<min)
			min=numere[i];
	}
	//mutex
	pthread_mutex_lock(&mtx);
	suma_minime+=min;
	pthread_mutex_unlock(&mtx);

	//barieraaaa
	pthread_barrier_wait(&barr);

	float medie=(float)(suma_minime/MAX_THR);
	printf("Thread %2d: media=%f\n",id,medie);
	return NULL;
}

int main(int argc, char* argv[])
{
	//generez 10000 de numere aleatoare
	srand(time(NULL));
	for(int i=0;i<MAX_NUM;i++)
	{
		numere[i]=rand();
	}
	//creez bariera
	pthread_barrier_init(&barr,NULL,MAX_THR);
	//creez thread-uri
	pthread_t tid[MAX_THR];
	for(int i=0;i<MAX_THR;i++)
	{
		int *id=malloc(sizeof(int));
		*id=i;
		pthread_create(&tid[i],NULL,do_work,id);
	}
	//astept terminarea
	for(int i=0;i<MAX_THR;i++)
	{
		pthread_join(tid[i],NULL);
	}
	//distrug barierea
	pthread_barrier_destroy(&barr);
	return 0;
}

    
