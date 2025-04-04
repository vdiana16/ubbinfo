#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <fcntl.h>

//Un client trimite unui server un sir de caractere. Serverul va returna clientului numarul de
//caractere spatiu din sir.

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Mod utilizare ./numefisier port\n");
		return 1;
	}

	struct sockaddr_in server;
	int c;
	c = socket(AF_INET, SOCK_STREAM, 0);
	if (c < 0) {
		printf("Eroare la crearea socketului client!\n");
                return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[1]));
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(c, (struct sockaddr*) &server, sizeof(server)) < 0) {
		printf("Eroare la conectarea la server!\n");
                return 1;
	}


	char* sir = (char*)malloc(sizeof(char)*1024);
	printf("Dati sirul:\n");
	fgets(sir, 1024, stdin);
	sir[strcspn(sir,"\n")] = '\0';

	uint16_t lg;
	lg = strlen(sir) + 1;
	lg = htons(lg);
	send(c, &lg, sizeof(uint16_t), 0);
	printf("Numarul bytes cititi %hu\n", ntohs(lg));
	int k = send(c, sir, sizeof(char) * ntohs(lg), 0);
	printf("Numarul bytes cititi %hu\n", k);

	uint16_t numarsp;
	recv(c, &numarsp, sizeof(uint16_t), 0);
	numarsp = ntohs(numarsp);
	printf("Numarul de spatii este: %hu\n", numarsp);

	free(sir);
	close(c);
}
