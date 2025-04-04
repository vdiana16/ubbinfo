#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>

#define NR_THR 10

pthread_barrier_t barr1;
//pthread_barrier_t barr2;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

int N;
int fd;
int numere[170000];
int fr[256] = {0}; // avem numere din intervalul 5..255
int suma = 0;
int print1 = 0;
int print2 = 0;
int nrAprMedie = INT_MAX;
float medie;
int numarP3;

void* doWork(void* arg){
        int id = *(int*)arg;
        free(arg);
        int st = id * (N/NR_THR);
        int dr = st + (N/NR_THR);
        for (int i = st; i < dr; i++){
                pthread_mutex_lock(&mtx);
                if ((numere[i] % 5 == 0) && (5 <= numere[i] && numere[i] <= 255) ){
                        fr[numere[i]]++;
                        suma++;
                }
                printf("%d, %d\n", numere[i], suma);
                pthread_mutex_unlock(&mtx);
        }
        //-----------------BARIERA------------------//
        pthread_barrier_wait(&barr1);
        pthread_mutex_lock(&mtx);
        if (print1 == 0){
                for (int i = 5; i <= 255; i+=5){
                        printf("Numarul %d apare de %d ori.\n", i, fr[i]);
                }
                print1 = 1;
        }
        //medie = (float)(suma/N);
        medie = (float)(suma/100);
        printf("Suma: %d, Medie: %f\n", suma, medie);
        for (int i = 5; i <= 255; i += 5){
                if (abs((int)(medie) - fr[i]) < nrAprMedie){
                        nrAprMedie = abs((int)(medie) - fr[i]);
                        numarP3 = fr[i];
                }
        }
        if (print2 == 0){
                for (int i = 5; i <= 255; i += 5){
                        if (fr[i] == numarP3){
                                printf("Numar cu frecventa ce mai aporpiata de medie: %d\n", i);
                        }
                }
                print2 = 1;
        }
        pthread_mutex_unlock(&mtx);
        return NULL;
}

int main(int argc, char* argv[]){
        //Citesc N.
        printf("N {9000,10000,170000}: ");
        scanf("%d", &N);

        //Citesc din fisier.
        fd = open("random-file", O_RDONLY);
        if (fd == -1){
                perror("open()");
                exit(1);
        }
        for (int i = 0; i < N; i++){
                read(fd, &numere[i], 1);
        }

        //Initializez barieria.
        pthread_barrier_init(&barr1, NULL, NR_THR);
        //pthread_barrier_init(&barr2, NULL, NR_THR);

        //Creez threadurile.
        pthread_t tid[NR_THR];
        for (int i = 0; i < NR_THR; i++){
                int* id =(int*) malloc(sizeof(int));
                *id = i;
                pthread_create(&tid[i], NULL, doWork, id);
        }

        //Astept terminarea threadurilor.
        for(int i = 0; i < NR_THR; i++){
                pthread_join(tid[i], NULL);
        }

        //Distrug bariera.
        pthread_barrier_destroy(&barr1);
        //pthread_barrier_destory(&barr2);
        return 0;
}
