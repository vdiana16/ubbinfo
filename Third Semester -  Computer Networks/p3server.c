#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define CAPACITY 1024

void deservireclient(int c) {
	char* sir = (char*)malloc(sizeof(char) * CAPACITY);
	int octetiprim = recv(c, sir, sizeof(char) * CAPACITY, 0);
	printf("Am primit sirul %s\n", sir);
        sir[octetiprim] = '\0';
	char* sirogl = (char*)malloc(sizeof(char) * (octetiprim + 1));
	int k = octetiprim - 2;
	for (int i = 0; i < octetiprim; i++) {
		sirogl[i] = sir[k];
		k--;
	}
	sirogl[octetiprim] = '\0';
	send(c, sirogl, strlen(sir) + 1, 0);
	free(sir);
	free(sirogl);
	close(c);

}

int main() {
	int s, c, l;
	struct sockaddr_in server, client;

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

	listen(s, 5);
	l = sizeof(client);

	memset(&client, 0, sizeof(client));
	while(1) {
		c = accept(s, (struct sockaddr*) &client, &l);
		printf("S-a conectat un client.\n");

		deservireclient(c);
	}

}
