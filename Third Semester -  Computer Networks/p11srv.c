#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void deservire_client(int c) {
	uint16_t lg;
	recv(c, &lg, sizeof(uint16_t), 0);
	lg = ntohs(lg);
	char* sir = (char*)malloc(sizeof(char)*lg);

	int k = recv(c, sir, sizeof(char) * lg, MSG_WAITALL);
	printf("Am primit %d bytes\n", k);

	uint16_t contor = 0;
	for(int i = 0; i < lg - 1; i++) {
		if (sir[i] == ' ') {
			contor++;
		}
	}
	contor = htons(contor);
	send(c, &contor, sizeof(uint16_t), 0);

	free(sir);
	close(c);
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Mod de utilizare ./numefisier port\n");
		return 1;
	}

	int s, c, l;
	struct sockaddr_in server, client;

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
		printf("Eroare la crearea socketului server!\n");
                return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[1]));
	server.sin_addr.s_addr = INADDR_ANY;

	if (bind(s, (struct sockaddr*) &server, sizeof(server)) < 0) {
	        printf("Eroare la deschiderea serverului!\n");
                return 1;
	}

	listen(s, 5);
	l = sizeof(client);
	memset(&client, 0, sizeof(client));
	while (1) {
		c = accept(s, (struct sockaddr*) &client, &l);
		printf("S-a conectat un client.\n");
		if (fork() == 0) {
			deservire_client(c);
			printf("Client deconectat.\n");
			return 0;
		}
	}
	close(s);
}
