#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THR 10
#define MAX_SIZE 100
#define GOL 0
#define PLIN  1

int fd;
int suma=0;
int buffer[100];
int stare=GOL; //0-GOL, 1-PLIN

pthread_cond_t gol = PTHREAD_COND_INITIALIZER;
pthread_cond_t plin = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* produce(void* arg)
{
	int id=*(int*)arg;
	free(arg);
	//daca bufferul e Plin
	//astept sa devina Gol
	pthread_mutex_lock(&mtx);
	while(stare==PLIN)
	{
		pthread_cond_wait(&gol,&mtx);
	}
	for(int i=0;i<MAX_SIZE;i++)
	{
		read(fd,&buffer[i],sizeof(int));
	}
	stare=PLIN;
	//trezeste cel putin 1
	pthread_cond_signal(&plin);
	//pthread_cond_broadcast(&cv) le trezeste pe toate
	pthread_mutex_unlock(&mtx);
	return NULL;
}

void* consume(void* arg)
{
	int id=*(int*)arg;
        free(arg);
	//daca bufferul e Gol
	//astept sa devina Plin
	pthread_mutex_lock(&mtx);
        while(stare==GOL)
        {
                pthread_cond_wait(&plin,&mtx);
        }
	for(int i=0;i<MAX_SIZE;i++)
        {
		suma+=buffer[i];
        }
	stare=GOL;
        //trezeste cel putin 1
        pthread_cond_signal(&gol);
        //pthread_cond_broadcast(&cv) le trezeste pe toate
        pthread_mutex_unlock(&mtx);
	return NULL;
}

int main(int argc,char* argv[])
{
	//deschid fisierul
	fd=open("file.bin",O_RDONLY);
	//creez thread-uri
	pthread_t tc[MAX_THR];
	for(int i=0;i<MAX_THR;i++)
	{
		int* id=malloc(sizeof(int));
		*id=i;
		pthread_create(&tc[i],NULL,consume,id);
	}
	pthread_t tp[MAX_THR];
	for(int i=0;i<MAX_THR;i++)
        {
                int* id=malloc(sizeof(int));
                *id=i;
                pthread_create(&tp[i],NULL,produce,id);
        }
	for(int i=0;i<MAX_THR;i++)
        {
   		pthread_join(tc[i],NULL);
                pthread_join(tp[i],NULL);
        }
	printf("Suma %d\n",suma);
	close(fd);
	return 0;
}
