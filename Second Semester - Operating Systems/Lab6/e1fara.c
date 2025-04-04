#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

//problema 31 de pe site

typedef struct{
	int* stop;
	pthread_barrier_t *barr;
	pthread_mutex_t *mtx;

}

void* do_work(void* arg)
{
	data td=*((*data*)arg);
        pthread_barrier_wait(td.barr);
        while(1)
        {
                //sectiune critica
                pthread_mutex_lock(td.mtx);
                if(*(td.stop)==0)
                {
                        int nr=rand()%111112;
                        printf("%d\n",nr);
                        if(nr%1001==0)
                        {
                                *(td.stop)=1;
                                break;
                        }
                }
                else
                {
                        break;
                }
                pthread_mutex_unlock(td.mtx);
        }
        //atentie aici
        pthread_mutex_unlock(td.mtx);
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
	int *st=malloc(sizeof(int));
	pthread_barrier_t *ba = malloc(sizeof(pthread_barrier_t)); // ca sa fie accesibil si in alte threaduri
	pthread_barrier_init(ba,NULL,N);
	pthread_mutex_t *mt=malloc(sizeof_pthread_mutex_t));
	pthread_mutex_init(mt,NULL);

        srand(time(NULL));   //pentru a nu se genera aceleasi numere

        pthread_t tid[N];
        data *args=malloc(N*sizeof(data));

	for(int i=0;i<N;i++)
        {
		args[i].stop=0;
		args[i].barr=ba;
		args[i].mtx=mt;
                pthread_create(&tid[i],NULL,do_work,args[i]);
        }
        for(int i=0;i<N;i++)
        {
                pthread_join(tid[i],NULL);
        }
        pthread_barrier_destroy(ba);
	pthread_mutex_destroy(mtx);
	free(args);
	free(st);
	free(ba);
	free(mt);
        return 0;
}
