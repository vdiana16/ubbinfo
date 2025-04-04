/*

27. Scrieti un program C care primeste doua numere, N si M, ca argumente la linia de comanda. Programul creeaza N thread-uri "generator" care genereaza litere mici ale alfabetului aleator si le adauga unui sir de caractere cu 128 de pozitii. Programul mai creeaza un thread "printer" care asteapta ca toate pozitiile sirului de caractere sa fie ocupate, moment in care afiseaza sirul si apoi seteaza toate pozitiile sirului la NULL. Cele N thread-uri "generator" vor genera M astfel de string-uri, iar thread-ul "printer" va afisa fiecare string imediat ce ajunge la lungimea 128.

*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define SIZE 128

int pos;
int count;
char buffer[SIZE+1];
pthread_cond_t cg = PTHREAD_COND_INITIALIZER;
pthread_cond_t cp = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* generate(void* arg)
{
	while (1)
	{
		char ch = 'a' + rand() % ('z' - 'a' + 1);
		
		pthread_mutex_lock(&mtx);
		if (pos == SIZE)
		{
			pthread_cond_signal(&cp);
			while (pos == SIZE)
				pthread_cond_wait(&cg, &mtx);
		}
		
		if (count == 0)
			break;
		
		buffer[pos] = ch;
		pos++;
		pthread_mutex_unlock(&mtx);
	}
	pthread_mutex_unlock(&mtx);
	
	return NULL;
}

void* print(void* arg)
{
	while(1)
	{
		pthread_mutex_lock(&mtx);
		if (pos != SIZE)
		{
			pthread_cond_signal(&cg);
			while (pos != SIZE)
				pthread_cond_wait(&cp, &mtx);
		}
		
		// afisez sirul de caractere
		printf("%s\n", buffer);
	
		// reinitializez sirul de caractere
		memset(buffer, 0, SIZE * sizeof(char));
	
		pos = 0;
		count--;
		pthread_cond_broadcast(&cg);
		
		if (count == 0)
			break;
		
		pthread_mutex_unlock(&mtx);
	}
	pthread_mutex_unlock(&mtx);
	
	return NULL;
}


int main(int argc, char* argv[])
{
	// verific numarul de argumente
	if (argc < 3)
	{
		printf("Trebuie sa furnizati 2 argumente.\n");
		printf("Utilizare: %s N M\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	// obtin N, M
	int N = atoi(argv[1]);
	int M = atoi(argv[2]);
	
	// initializez variabilele globale
	pos = 0;
	count = M;
	memset(buffer, 0, (SIZE + 1) * sizeof(char));	// initializez sirul de caractere
	
	// initializez generatorul de numere aleatoare
	srand(time(NULL));
	
	// creez cele N thread-uri "generator"
	pthread_t tid[N + 1];
	for (int i = 0; i < N; i++)
		pthread_create(&tid[i], NULL, generate, NULL);
	
	// creez thread-ul "printer"
	pthread_create(&tid[N], NULL, print, NULL);
	
	// astept terminarea thread-urilor
	for (int i = 0; i < (N + 1); i++)
		pthread_join(tid[i], NULL);

	return 0;
}

