#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX_THR 100

void* do_work(void* a)
{
	int k=*(int*)a;
	free(a);
	printf("Eu sunt thread-ul %d\n",k);
	return NULL;
}

int main(int argc, char* argv[])
{
	pthread_t tid[MAX_THR];
	for(int i=0;i<MAX_THR;i++)
	{
		int *p=(int*)malloc(sizeof(int));
		*p=i;
		pthread_create(&tid[i],NULL,do_work,p);
	}
	for(int i=0;i<MAX_THR;i++)
	{
		pthread_join(tid[i],NULL);
	}
	return 0;
}
