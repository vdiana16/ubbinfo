#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define CAPACITY 150

int main() {
	int s;
	struct sockaddr_in server, client;
	int c, l;

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
		printf("Eroare la crearea socketului server!\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	if (bind(s, (struct sockaddr*) &server, sizeof(server)) < 0) {
		printf("Eroare la bind!\n");
		return 1;
	}

	listen(s,5);
	l = sizeof(client);
	memset(&client, 0, sizeof(client));
	while (1){
		c = accept(s, (struct sockaddr*) &client, &l);
		printf("S-a conectat un client. \n");

		//deservirea clientului
		uint16_t n, nrdiv = 0;
		recv(c, &n, sizeof(uint16_t), MSG_WAITALL);
		n = ntohs(n);
		uint16_t* divizori = (uint16_t*)malloc(sizeof(uint16_t)*CAPACITY);
		for (uint16_t d = 1; d <= n; d++) {
			if (n % d == 0) {
 				divizori[nrdiv++] = htons(d);
				/*if (d * d < n) {
					uint16_t aux = n/d; // d!=sqrt(n)
					divizori[nrdiv++] = htons(aux);
				}
				*/
			}
		}
		uint16_t m = nrdiv;
		nrdiv = htons(nrdiv);
		send(c, &nrdiv, sizeof(nrdiv), 0);
		send(c, divizori, sizeof(uint16_t) * m, 0);
		free(divizori);
		close(c);
	}
}
