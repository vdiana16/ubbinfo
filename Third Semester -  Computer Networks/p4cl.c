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

//Un client trimite unui server doua siruri de caractere ordonate. Serverul va interclasa cele doua
//siruri si va returna clientului sirul rezultat interclasat.


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
        char* sir1 = (char *)malloc(sizeof(char) * 1024);
        printf("Dati sirul de caractere: ");
        fgets(sir1, 1024, stdin);
        sir1[strcspn(sir1,"\n")] = '\0'; //elimin newline-ul de la sfarsitul sirului
        uint16_t lgsir1, lg1;
 	lgsir1 = strlen(sir1) + 1;
        lg1 = lgsir1;
        lgsir1 = htons(lgsir1);
        send(c, &lgsir1, sizeof(uint16_t), 0);

        printf("Numarul bytes cititi %hu\n", lg1);
        int k1 = send(c, sir1, lg1, 0);
        printf("Numar bytes trimisi: %d\n", k1);

	//citesc al doilea sir
	char* sir2 = (char *)malloc(sizeof(char) * 1024);
        printf("Dati sirul de caractere: ");
        fgets(sir2, 1024, stdin);
        sir2[strcspn(sir2,"\n")] = '\0'; //elimin newline-ul de la sfarsitul sirului
        uint16_t lgsir2, lg2;
        lgsir2 = strlen(sir2) + 1;
        lg2 = lgsir2;
        lgsir2 = htons(lgsir2);
        send(c, &lgsir2, sizeof(uint16_t), 0);

        printf("Numarul bytes cititi %hu\n", lg2);
        int k2 = send(c, sir2, lg2, 0);
        printf("Numar bytes trimisi: %d\n", k2);

	uint16_t lg3;
	lg3 = lg1 + lg2 - 1;
        char* sirinterclasat = (char*)malloc(sizeof(char)*1024);
        recv(c, sirinterclasat, lg3, MSG_WAITALL);
        printf("Sirul interclasat este: %s\n", sirinterclasat);

        free(sirinterclasat);
	free(sir2);
	free(sir1);
        close(c);
}


