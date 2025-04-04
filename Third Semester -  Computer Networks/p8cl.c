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

//Un client trimite unui server doua siruri de numere. Serverul va returna clientului sirul de numere
//comune celor doua siruri primite.

#define CAPACITY 1024

struct structNr{
	uint16_t lg;
	uint16_t* numere;
};

struct structNr numereDinSir(char* sir) {
	uint16_t lgnr = 0;
	uint16_t* nr = (uint16_t*)malloc(sizeof(uint16_t)*CAPACITY);

	char* tmp = strtok(sir, " ");
	while (tmp) {
		nr[lgnr] = htons(atoi(tmp));
		lgnr++;
		tmp = strtok(NULL, " ");
	}

	struct structNr s;
	s.lg = htons(lgnr);
	s.numere = nr;

	return s;
}

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

	//citesc primul sir
        char* sirnr = (char*)malloc(sizeof(char)*CAPACITY);
        printf("Dati numerele primului sir separate prin spatiu: ");
        fgets(sirnr,CAPACITY,stdin);
	struct structNr s1 = numereDinSir(sirnr);

	printf("%hu\n", ntohs(s1.lg));
	send(c, &s1.lg, sizeof(uint16_t), 0);
        send(c, s1.numere, sizeof(uint16_t) * ntohs(s1.lg), 0);

	//citesc al doilea sir
	char* sirnr2 = (char*)malloc(sizeof(char)*CAPACITY);
        printf("Dati numerele celui de-al doilea sir separate prin spatiu: ");
        fgets(sirnr2,CAPACITY,stdin);
        struct structNr s2 = numereDinSir(sirnr2);

	printf("%hu\n", ntohs(s2.lg));
	send(c, &s2.lg, sizeof(uint16_t), 0);
        send(c, s2.numere, sizeof(uint16_t) * ntohs(s2.lg), 0);

	uint16_t lungimesir;
	recv(c, &lungimesir, sizeof(uint16_t), 0);
	lungimesir = ntohs(lungimesir);

	if (lungimesir == 0) {
		printf("Nu exista numere comune.\n");
	}
	else {
		uint16_t* nrsir = (uint16_t*)malloc(sizeof(uint16_t)*1024);
        	recv(c, nrsir, sizeof(uint16_t)*lungimesir, MSG_WAITALL);
		printf("Sirul de numere comune este:\n");
        	for (int i = 0; i < lungimesir; i++) {
                	printf("%hu ", nrsir[i]);
        	}
        	printf("\n");
		free(nrsir);
	}

        close(c);
}


