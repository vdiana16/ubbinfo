#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

void deservire_client(int c) {
        uint16_t numar;
        recv(c, &numar, sizeof(uint16_t), 0);
        numar = ntohs(numar);

	uint16_t* divizori = (uint16_t*)malloc(sizeof(uint16_t)*1024);
	uint16_t nrdivizori = 0;
	for (uint16_t i = 1; i <= numar; i++)
	{
		if (numar % i == 0) {
			divizori[nrdivizori++] = htons(i);
		}
	}

	uint16_t lg = nrdivizori;
	nrdivizori = htons(nrdivizori);
        send(c, &nrdivizori, sizeof(uint16_t), 0);
	send(c, divizori, sizeof(uint16_t) * lg, 0);

        free(divizori);
        close(c);
}

int main(int argc, char* argv[]) {
        if(argc < 2) {
                printf("Eroare! Mod utilizare: ./client port_number");
                return 1;
        }

        int s, c, l;
        struct sockaddr_in server, client;

        s = socket(AF_INET, SOCK_STREAM, 0);
        if (s < 0) {
                printf("Eroare la crearea socketului server\n");
                return 1;
        }

        memset(&server, 0, sizeof(server));
        server.sin_port = htons(atoi(argv[1]));
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;

        if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
                printf("Eroare la bind\n");
                return 1;
        }

        listen(s, 5);
        l = sizeof(client);
	memset(&client, 0, sizeof(server));
        while (1) {
                c = accept(s, (struct sockaddr *) &server, &l);
                printf("S-a conectat un client.\n");
                if (fork() == 0) {
                        deservire_client(c);
                        printf("Client deconectat.\n");
                        return 0;
                }
        }
	close(s);
}

