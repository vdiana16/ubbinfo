#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 1024

//Un client trimite unui server doua siruri de caractere ordonate. Serverul va interclasa cele doua
//siruri si va returna clientului sirul rezultat interclasat.

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

        if (connect(c, (struct sockaddr*) &server, sizeof(server)) < 0) {
                printf("Eroare la conectarea la server!\n");
                return 1;
        }

        char* sir1 = (char*)malloc(sizeof(char)*CAPACITY);
	printf("Dati primul sir de caractere ordonate: ");
      	fgets(sir1, CAPACITY, stdin);
        sir1[strcspn(sir1,"\n")] = '\0';  //elimin linia noua
	printf("Am citit sirul %s\n", sir1);
	uint16_t lg1 = strlen(sir1);

	char* sir2 = (char*)malloc(sizeof(char)*CAPACITY);
        printf("Dati al doilea sir de caractere ordonate: ");
        fgets(sir2, CAPACITY, stdin);
        sir2[strcspn(sir2,"\n")] = '\0';  //elimin linia noua
        printf("Am citit sirul %s\n", sir2);
	uint16_t lg2 = strlen(sir2);

	lg1 = htons(lg1);
        send(c, &lg1, sizeof(int), 0);
	send(c, sir1, strlen(sir1), 0); // +1 terminatorul
	lg2 = htons(lg2);
	send(c, &lg2, sizeof(int), 0);
	send(c, sir2, strlen(sir2), 0);

	uint16_t lg;
	recv(c, &lg, sizeof(uint16_t), MSG_WAITALL);
        char* sirinter = (char*)malloc(sizeof(char) * lg);
        recv(c, sirinter, sizeof(char) * lg, MSG_WAITALL);
	sirinter[lg] = '\0';
	puts(sirinter);

        free(sir1);
        free(sir2);
	free(sirinter);
        close(c);
}
