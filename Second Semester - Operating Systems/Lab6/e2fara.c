#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

#define SIZE 128

//problema 27

int count;
char buffer[SIZE+1];
int poz;

pthread_cond_t cg=PTHREAD_COND_INITIALIZER;
pthread_cond_t cp=PTHREAD_COND_INITIALIZER;
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;


void* generate(void* argc)
{
        while(1)
        {
                pthread_mutex_lock(&mtx);
                if(poz==SIZE)
                {
                        pthread_cond_signal(&cp);
                        while(poz==SIZE)
                        {
                                pthread_cond_wait(&cg,&mtx);
                        }
                }
                if(count==0)
                {
                        break;
                }
                char ch='a' + rand() % ('z'-'a'+1);
                buffer[poz]=ch;
                poz++;
                pthread_mutex_unlock(&mtx);
        	}
 	}
        //pt break
        pthread_mutex_unlock(&mtx);
        return NULL;
}

void* print(void* argc)
{
        while(1)
        {
                pthread_mutex_lock(&mtx);
                if(poz!=SIZE)
                {
                        pthread_cond_signal(&cg);
                        while(poz!=SIZE)
                        {
                                pthread_cond_wait(&cp,&mtx);
                        }
                }
                printf("%s\n",buffer);
                count--;
                poz=0;
                memset(buffer,0,SIZE);
                pthread_cond_broadcast(&cg);
                if(count==0)
                {
                        break;
                }
                pthread_mutex_unlock(&mtx);
        }
        pthread_mutex_unlock(&mtx);
        return NULL;
}

int main(int argc, char* argv[])
