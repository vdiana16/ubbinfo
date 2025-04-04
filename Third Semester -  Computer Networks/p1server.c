#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define CAPACITY 150

int main() {
	int s;
	struct sockaddr_in server, client;
	int c, l;

	//creeez socketul pentru server
  	s = socket(AF_INET, SOCK_STREAM, 0);
  	if (s < 0) {
   		printf("Eroare la crearea socketului server\n");
    		return 1;
  	}

	//initializez blocul de memorie care retine detaliile despre de server
  	memset(&server, 0, sizeof(server));
  	server.sin_port = htons(1234);
  	server.sin_family = AF_INET;
  	server.sin_addr.s_addr = INADDR_ANY;

	//fac disponibil serverul pentru a accepta conexiuni de la clienti
	if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
    		printf("Eroare la bind\n");
    		return 1;
  	}

	//creez coada de asteptare
	listen(s, 5);
	l = sizeof(client);

  	memset(&client, 0, sizeof(client));
	while (1) {
		//accept clientul
		c = accept(s, (struct sockaddr *) &client, &l);
    		printf("S-a conectat un client.\n");

		// deservirea clientului
		uint16_t lg, suma = 0;
		recv(c, &lg, sizeof(lg), MSG_WAITALL);
		lg = ntohs(lg);
                uint16_t* numere = (uint16_t *)malloc(sizeof(uint16_t) * lg);
    		recv(c, numere, sizeof(uint16_t) * lg, MSG_WAITALL);
		for(int i = 0; i < lg; i++){
			suma += ntohs(numere[i]);
		}
		suma = htons(suma);
    		send(c, &suma, sizeof(suma), 0);

		free(numere);
		close(c);
    		// sfarsitul deservirii clientului;
  }
}
