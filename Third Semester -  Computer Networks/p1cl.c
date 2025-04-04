#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define CAPACITY 1024
#define CAPACITY2 350

//Un client trimite unui server un sir de numere. Serverul va returna clientului suma numerelor
//primite

int main(int argc,char* argv[]){
	if (argc < 2){
		printf("Ai uitat de port!\n");
		return 1;
	}

	int c;
	struct sockaddr_in server;

	//creez socket-ul
	c = socket(AF_INET, SOCK_STREAM, 0);
	if (c < 0){
		printf("Eroare la crearea socketului client\n");
                return 1;
	}

	//initializez informatiile utile pentru server
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(atoi(argv[1]));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	//realizez conectarea la server
	if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0){
		printf("Eroare la conectarea la server\n");
                return 1;
	}


	//primesc datele
	char* numere = (char *)malloc(sizeof(char)*CAPACITY);
	printf("Dati numerele separate prin spatii: ");
	fgets(numere,CAPACITY,stdin);

	uint16_t lg = 0;
	uint16_t* nr = (uint16_t*)malloc(sizeof(uint16_t)*CAPACITY2);
	char* part = strtok(numere," ");
	while (part){
		nr[lg] = htons(atoi(part));
		lg++;
		part = strtok(NULL, " ");
	}

	lg = htons(lg);

	//trimit datele
	send(c, &lg, sizeof(uint16_t), 0);
	send(c, nr, sizeof(uint16_t)*lg, 0);
	printf("Numere trimise cu succes!\n");

	//primesc rezultatul
	uint16_t suma;
	recv(c, &suma, sizeof(suma), 0);
	suma = ntohs(suma);
	printf("Suma numerelor este %hu\n", suma);

	free(nr);
	free(numere);
	//inchid socketul client
	close(c);
}
