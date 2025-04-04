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

//Un client trimite unui server un sir de caractere si doua numere (fie acestea s, i, l). Serverul
//va returna clientului subsirul de lungime l a lui s care incepe la pozitia i.

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

        //citesc sirul
        char* sir = (char *)malloc(sizeof(char) * 1024);
        printf("Dati sirul de caractere: ");
        fgets(sir, 1024, stdin);
        sir[strcspn(sir,"\n")] = '\0'; //elimin newline-ul de la sfarsitul sirului
        uint16_t lgsir, lg;
 	lgsir = strlen(sir) + 1;
        lg = lgsir;
        lgsir = htons(lgsir);
        send(c, &lgsir, sizeof(uint16_t), 0);
	printf("Numarul bytes cititi %hu\n", lg);
        int k = send(c, sir, lg, 0);
        printf("Numar bytes trimisi: %d\n", k);

	uint16_t poz;
       	printf("Dati pozitia: ");
	scanf("%hu", &poz);
	uint16_t pozcop = poz;
        poz = htons(poz);
        send(c, &poz, sizeof(uint16_t), 0);

	uint16_t l;
        printf("Dati lungimea: ");
        scanf("%hu", &l);
        l = htons(l);
        send(c, &l, sizeof(uint16_t), 0);

	uint16_t lgsubsir;
	recv(c, &lgsubsir, sizeof(uint16_t), 0);
	lgsubsir = ntohs(lgsubsir);
        char* subsir = (char *)malloc(sizeof(char)*1024);
        recv(c, subsir, sizeof(char) * lgsubsir, 0);
	if (subsir[0] == '\0'){
		printf("Subsir inexistent!\n");
	}
	else {
	        printf("Subsirul care incepe pe pozitia %hu de lungime %hu este: %s\n", pozcop, lgsubsir, subsir);
	}

	free(subsir);
        free(sir);
        close(c);
}


