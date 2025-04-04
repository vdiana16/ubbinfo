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

//Un client trimite unui server un sir de caractere. Serverul va returna clientului numarul de
//caractere spatiu din sir.

int main(int argc, char* argv[]){
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

	uint16_t numar;
	recv(c, &numar, sizeof(uint16_t), 0);
	numar = ntohs(numar);
	printf("Numarul de spatii goale din sirul citit este: %hu\n",numar);

	free(sir);
	close(c);
}
