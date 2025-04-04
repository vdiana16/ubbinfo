#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

//Un client trimite unui server un numar. Serverul va returna clientului sirul divizorilor acestui
// numar.

int main() {
	int c;
	struct sockaddr_in server;

	c = socket(AF_INET, SOCK_STREAM, 0);
	if (c < 0) {
		printf("Eroare la crearea socketului client!\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(c, (struct sockaddr*) &server, sizeof(server)) < 0) {
		printf("Eroare la conectarea la server!\n");
		return 1;
	}

	uint16_t n;
	printf("n= ");
	scanf("%hu", &n);
	n = htons(n);
	send(c, &n, sizeof(uint16_t), 0);

	uint16_t nrdiv;
	recv(c, &nrdiv, sizeof(uint16_t), MSG_WAITALL);
	nrdiv = ntohs(nrdiv);
	uint16_t* divizori = (uint16_t*)malloc(sizeof(uint16_t)*nrdiv);
	recv(c, divizori, sizeof(uint16_t) * nrdiv, MSG_WAITALL);
	printf("Sirul divizorilor numarului %hu este: \n", ntohs(n));
	for(int i = 0; i < nrdiv; i++) {
		printf("%hu ", ntohs(divizori[i]));
	}
	printf("\n");
	free(divizori);
	close(c);
}
