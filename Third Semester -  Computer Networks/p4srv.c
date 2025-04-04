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
        //primesc primul sir
	uint16_t lgsir1;
        recv(c, &lgsir1, sizeof(uint16_t), 0);
        lgsir1 = ntohs(lgsir1);
        printf("Am primit lg sir1: %hu\n", lgsir1);

        char* sir1 = (char*)malloc(sizeof(char)*1024);
        int k1 = recv(c, sir1, lgsir1, MSG_WAITALL);
        printf("Numarul de bytes primiti este: %d\n", k1);

	//primesc al doilea sir
        uint16_t lgsir2;
        recv(c, &lgsir2, sizeof(uint16_t), 0);
        lgsir2 = ntohs(lgsir2);
        printf("Am primit lg sir2: %hu\n", lgsir2);

        char* sir2 = (char*)malloc(sizeof(char)*1024);
        int k2 = recv(c, sir2, lgsir2, MSG_WAITALL);
        printf("Numarul de bytes primiti este: %d\n", k2);

	char* sir3 = (char*)malloc(sizeof(char)*1024);
	uint16_t lgsir3 = 0;

	int i = 0, j = 0;
	while (i < lgsir1 - 1 && j < lgsir2 - 1) {
		if (sir1[i] < sir2[j]) {
			sir3[lgsir3++] = sir1[i++];
		}
		else {
			sir3[lgsir3++] =sir2[j++];
		}
	}
	while (i < lgsir1 - 1) {
		sir3[lgsir3++] = sir1[i++];
	}
	while (j < lgsir2 - 1) {
		sir3[lgsir3++] = sir2[j++];
	}
	sir3[lgsir3] = '\0';
	lgsir3++;

	int k3 = send(c, sir3, lgsir3, MSG_WAITALL);
        printf("Numarul de bytes trimisi este: %d\n", k3);

        free(sir3);
	free(sir2);
	free(sir1);
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
}

