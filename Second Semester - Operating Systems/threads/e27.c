#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 128

typedef struct{
	int *poz;
	int *contor;
	char *buffer[SIZE+1];
	pthread_mutex_t *mtx=PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t *cg=PTHREAD_COND_INITIALIZER;
	pthread_cond_t *cp=PTHREAD_COND_INITIALIZER;
}

void* generator(void* arg)
{
	data td=*((data *)arg);
	while(1)
	{
		char ch='a'+rand()%('z'-'a'+1);
		pthread_mutex_lock(td.mtx);
		if(*td.poz==SIZE)
		{
			pthread_cond_signal(td.cp);
			while(*td.poz==SIZE)
			{
				pthread_cond_wait(td.cg,td.mtx);
			}
		}
		if(*td.contor==0)
			break;
		td.buffer[*td.poz]=ch;
		*(td.poz)++;
		pthread_mutex_unlock(td.mtx);
	}
	pthread_mutex_unlock(td.mtx);
	return NULL;
}

void* printer(void* arg)
{
	td=*((data*)arg);
	while(1)
	{
		pthread_mutex_lock(td.mtx);
		if(*td.poz!=SIZE)
		{
			pthread_cond_signal(td.cg);
			while(*td.poz!=SIZE)
			{
				pthread_cond_wait(td.cp,td.mtx);
			}
		}
		printf("%s\n",td.buffer);
		memset(td.buffer,0,SIZE*sizeof(char));
		*td.poz=0;
		(*td.contor)--;
		pthread_cond_broadcast(td.cg);
		if((*td.contor)==0)
		{
			break;
		}
		pthread_mutex_unlock(td.mtx);
	}
	pthread_mutex_unlock(td.mtx);
	return NULL;
}


int main(int argc, char* argv[])
{
	if(argc!=3)
	{
		printf("Mai incearca");
	}
	int N,M;
	N=atoi(argv[1]);
	M=atoi(argv[2]);
	char *buffer=malloc((SIZE+1)*sizeof(char));
	char *poz=malloc(sizeof(int));
	//char *contor=malloc(sizeof(int));
	poz=0;
	memset(buffer,0,(SIZE+1)*sizeof(char));
	srand(time(NULL));
	pthread_mutex_t *mtx=malloc(sizeof(pthread_mutex_t));
	pthread_cond_t *cg=malloc(sizeof(pthread_cond_t));
	pthread_cond_t *cp=malloc(sizeof(pthread_cond_t));
	pthread_t tid[N+1];
	data *args=malloc((N+1)*sizeof(data));
	for(int i=0;i<N;i++)
	{
		args[i].poz=poz;
		args[i].contor=&M;
		args[i].buffer=buffer;
		args[i].cp=cp;
		args[i].cg=cg;
		args[i].mtx=mtx;
		pthread_create(&tid[i],NULL,generator,NULL);
	}
	args[N].poz=poz;
        args[N].contor=&M;
        args[N].buffer=buffer;
        args[N].cp=cp;
        args[N].cg=cg;
        args[N].mtx=mtx;
	pthread_create(&tid[N],NULL,printer,NULL);
	for(int i=0;i<=N;i++)
	{
		pthread_join(tid[i],NULL);
	}
	pthread_cond_destroy(cg);
	pthread_cond_destroy(cp);
	pthread_cond_destroy(mtx);
	free(poz);
	free(buffer);
	free(mtx);
	free(cg);
	free(cp);
	free(args);
	return 0;
}
