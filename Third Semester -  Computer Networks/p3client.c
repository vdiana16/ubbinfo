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

//Un client trimite unui server un sir de caractere. Serverul va returna clientului acest sir
// oglindit (caracterele sirului in ordine inversa).

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

	char* sir = (char*)malloc(sizeof(char)*CAPACITY);
	fgets(sir, CAPACITY, stdin);
	printf("Am citit sirul %s\n", sir);
	sir[strcspn(sir,"\n")] = '\0';  //elimin linia noua
	int lg = send(c, sir, strlen(sir) + 1, 0);

	char* sirogl = (char*)malloc(sizeof(char)*lg);
	int nroctetiprim = recv(c, sirogl, sizeof(char)*lg, 0);
	if (nroctetiprim > 0) {
		printf("Sirul %s are ca oglindit %s\n", sir, sirogl);
	}
	else {
		printf("Eroare la primirea mesajului!\n");
	}

	free(sir);
	free(sirogl);
	close(c);
}
