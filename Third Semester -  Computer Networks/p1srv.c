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

int main(int argc, char* argv[]){
	if(argc < 2) {
                printf("Eroare! Mod utilizare: ./server port_number\n");
                return 1;
        }

	int s, c, l;
	struct sockaddr_in server, client;

	//creez socketul pentru server
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
                printf("Eroare la crearea socketului server\n");
                return 1;
        }

	//initializez serverul cu informatiile utile
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(atoi(argv[1]));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	//fac disponibil serverul
	if (bind(s, (struct sockaddr*) &server, sizeof(server)) < 0){
		printf("Eroare la bind\n");
                return 1;
	}

	//creez coada de asteptare
	listen(s, 5);
	l = sizeof(client);

	//initializez clientul
	memset(&client, 0, sizeof(server));
	while (1){
		//accept clientul
		c = accept(s, (struct sockaddr*) &client, &l);
		printf("S-a conectat un client.\n");

		//deservire client
		uint16_t lg;
		recv(c, &lg, sizeof(lg), MSG_WAITALL);
		lg = ntohs(lg);
		uint16_t* nr = (uint16_t*)malloc(sizeof(uint16_t) * lg);
		recv(c, nr, sizeof(uint16_t) * lg, MSG_WAITALL);

		uint16_t suma = 0;
		for (int i = 0; i < lg; i++){
			suma += ntohs(nr[i]);
		}

		printf("Suma %hu\n", suma);
		printf("Trimitere suma \n");
		suma = htons(suma);
		send(c, &suma, sizeof(suma), 0);

		free(nr);
		printf("Suma trimisa cu succes!\n");
		close(c);
		//sfarsit deservire client
	}
}
