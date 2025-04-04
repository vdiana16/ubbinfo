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

//Un client trimite unui server un numar. Serverul va returna clientului sirul divizorilor acestui
//numar.

int main(int argc, char* argv[]) {
        if (argc < 2) {
                printf("Mod utilizare ./numefisier port.\n");
                return 1;
        }

        int c;
        struct sockaddr_in server;

        c = socket(AF_INET, SOCK_STREAM, 0);
        if (c < 0) {
                printf("Eroare la crearea socketuui client!\n");
                return 1;
        }

        memset(&server, 0, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_port = htons(atoi(argv[1]));
        server.sin_addr.s_addr = inet_addr("127.0.0.1");

        if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
                printf("Eroare la conectarea la server!\n");
                return 1;
        }

        //citesc numarul
        uint16_t numar;
	printf("Dati numarul: ");
	scanf("%hu", &numar);
        numar = htons(numar);
        send(c, &numar, sizeof(uint16_t), 0);

	uint16_t nrdivizori;
	recv(c, &nrdivizori, sizeof(uint16_t), 0);
        uint16_t* divizori = (uint16_t *)malloc(sizeof(uint16_t)*numar);
        recv(c, divizori, sizeof(uint16_t) * nrdivizori, MSG_WAITALL);
        printf("Sirul cu divizori este:\n");
	for(uint16_t i = 0; i < nrdivizori; i++) {
		printf("%hu ", ntohs(divizori[i]));
	}
	printf("\n");
        free(divizori);
        close(c);
}
