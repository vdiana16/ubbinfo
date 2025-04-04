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
	uint16_t lgs1;
        recv(c, &lgs1, sizeof(uint16_t), 0);
        lgs1 = ntohs(lgs1);
        printf("Am primit lg sir: %hu\n", lgs1);

        uint16_t* s1 = (uint16_t*)malloc(sizeof(uint16_t)*1024);
        int k1 = recv(c, s1, sizeof(uint16_t) * lgs1, MSG_WAITALL);
        printf("Numarul de bytes primiti este: %d\n", k1);

	//primesc al doilea sir
	uint16_t lgs2;
        recv(c, &lgs2, sizeof(uint16_t), 0);
        lgs2 = ntohs(lgs2);
        printf("Am primit lg sir: %hu\n", lgs2);

        uint16_t* s2 = (uint16_t*)malloc(sizeof(uint16_t)*1024);
        int k2 = recv(c, s2, sizeof(uint16_t) * lgs2, MSG_WAITALL);
        printf("Numarul de bytes primiti este: %d\n", k2);

	uint16_t lgs3 = 0;
	uint16_t* s3 = (uint16_t*)malloc(sizeof(uint16_t) * 1024);
	for(int i = 0; i < lgs1; i++) {
		for(int j = 0; j < lgs2; j++) {
			if (s1[i] == s2[j]) {
				s3[lgs3] = htons(s1[i]);
				lgs3++;
				break;
			}
		}
	}
	lgs3 = htons(lgs3);

	send(c, &lgs3, sizeof(uint16_t), 0);
	send(c, s3, sizeof(uint16_t) * ntohs(lgs3), 0);

	free(s3);
	free(s2);
	free(s1);
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

