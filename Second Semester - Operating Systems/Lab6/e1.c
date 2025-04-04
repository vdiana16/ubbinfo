    #include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

//problema 31 de pe site

pthread_barrier_t barr;
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;

int stop=0;

void* do_work(void* arg)
{
	pthread_barrier_wait(&barr);
	while(1)
	{
		//sectiune critica
		pthread_mutex_lock(&mtx);
		if(stop==0)
		{
			int nr=rand()%111112;
			printf("%d\n",nr);
			if(nr%1001==0)
			{
				stop=1;
				break;
			}
		}
		else
		{
			break;
		}
		pthread_mutex_unlock(&mtx);
	}
	//atentie aici
	pthread_mutex_unlock(&mtx);
	return NULL;
}


int main(int argc,char* argv[])
{
	if(argc!=2)
	{
		printf("Ai uitat N\n");
		exit(1);
	}
	int N=atoi(argv[1]);
	srand(time(NULL));   //pentru a nu se genera aceleasi numere
	pthread_barrier_init(&barr,NULL,N);
	pthread_t tid[N];
	for(int i=0;i<N;i++)
	{
		pthread_create(&tid[i],NULL,do_work,NULL);
	}
	for(int i=0;i<N;i++)
	{
		pthread_join(tid[i],NULL);
	}
	pthread_barrier_destroy(&barr);
	return 0;
}

    
