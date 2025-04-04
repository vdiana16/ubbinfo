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

#define CAPACITY 200

//Un client trimite unui server un sir de caractere. Serverul va returna clientului numarul de
//caractere spatiu din sir.

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

	if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la conectarea la server!\n");
		return 1;
	}

	char* sir = (char *)malloc(sizeof(char) * CAPACITY);
	fgets(sir, CAPACITY, stdin);
	sir[strcspn(sir, "\n")] = '\0';

	send(c, sir, strlen(sir) + 1, 0);

	uint16_t nrspatii;
	recv(c, &nrspatii, sizeof(nrspatii), 0);
	nrspatii = ntohs(nrspatii);
	printf("Numarul de spatii din sirul dat este: %hu\n", nrspatii);
	free(sir);

	close(c);
}
