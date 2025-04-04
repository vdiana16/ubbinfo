#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

#define CAPACITY 200

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

	if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la bind!\n");
		return 1;
	}

	listen(s, 5);
	l = sizeof(client);

	memset(&client, 0, sizeof(client));
	while (1) {
		c = accept(s, (struct sockaddr*) &client, &l);
		printf("S-a conectat un client.\n");

		uint16_t numarspatii = 0;
		char* sir = (char*)malloc(sizeof(char) * CAPACITY);
		int nrbiti = recv(c, sir, CAPACITY * sizeof(char), 0);
		sir[nrbiti] = '\0';
		for (int i = 0; i < nrbiti; i++) {
			if (sir[i] == ' ') {
				numarspatii++;
			}
		}
		numarspatii = htons(numarspatii);
		send(c, &numarspatii, sizeof(numarspatii), 0);

		close(c);
		free(sir);
	}
}
