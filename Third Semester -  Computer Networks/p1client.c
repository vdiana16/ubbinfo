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

#define CAPACITY 150
#define CAPACITY2 350

//Un client trimite unui server un sir de numere. Serverul va returna clientului suma numerelor primite.

int main() {
	int c;
	struct sockaddr_in server;

	//creez socket-ul pentru client
	c = socket(AF_INET, SOCK_STREAM, 0);
  	if (c < 0) {
		printf("Eroare la crearea socketului client\n");
		return 1;
  	}

	//intializez blocul de memorie pentru detaliile ce tin de server
	memset(&server, 0, sizeof(server));
 	server.sin_port = htons(1234);
  	server.sin_family = AF_INET;
  	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	//realizez conectarea la server
	if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
    		printf("Eroare la conectarea la server\n");
    		return 1;
  	}

	//citesc sirul de numere
	char* sir = (char *)malloc(sizeof(char) * CAPACITY2);
	printf("Dati numerele separate print spatiu: ");
	fgets(sir,CAPACITY2,stdin);

	//convertesc sirul de numere
	uint16_t lg = 0;
        uint16_t* numere = (uint16_t*)malloc(sizeof(uint16_t) * CAPACITY);
        char* tmp = strtok(sir," ");
        while(tmp){
                numere[lg++] = htons(atoi(tmp));
                tmp = strtok(NULL," ");
        }
        lg = htons(lg);

	//trimit informatiile utile
	send(c, &lg, sizeof(lg), 0);
  	send(c, numere, lg * sizeof(uint16_t), 0);

	//primesc informatiile cerute si le afisez
	uint16_t suma;
	recv(c, &suma, sizeof(suma), 0);
  	suma = ntohs(suma);
  	printf("Suma numerelor este: %hu\n", suma);

	free(numere);

	//inchid clientul
	close(c);
}
