    #include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int flag;
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barr;

void* generare(void* arg)
{
	int id=*(int*)arg;
	pthread_barrier_wait(&barr);
	while(1)
	{
		int nr=rand()%111112;
		pthread_mutex_lock(&mtx);
		if(flag==0)
		{
			printf("Thread %d: %d\n",id,nr);
			if(nr%1001==0)
			{
				flag=1;
				break;
			}
		}
		else
		{
			break;
		}
		pthread_mutex_unlock(&mtx);
	}
	pthread_mutex_unlock(&mtx);
	return NULL;
}

int main(int argc, char* argv[])
{
	int N=atoi(argv[1]);
	srand(time(NULL));
	pthread_t tid[N];
	pthread_barrier_init(&barr,NULL,N);
	flag=0;
	for (int i = 0; i < N; i++)
	{
		int *p=(int*)malloc(sizeof(int));
		*p=i;
		pthread_create(&tid[i], NULL, generare, p);
	}
	// astept terminarea thread-urilor
	for (int i = 0; i < N; i++)
	{
		pthread_join(tid[i], NULL);
	}
	pthread_barrier_destroy(&barr);
	return 0;
}

    
