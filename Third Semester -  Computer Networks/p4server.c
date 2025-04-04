#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define CAPACITY 1024

void deservireclient(int c) {
        uint16_t lg1;
	recv(c, &lg1, sizeof(int), MSG_WAITALL);
	lg1 = ntohs(lg1);
	char* sir1 = (char*)malloc(sizeof(char) * lg1);
	recv(c, sir1, sizeof(char) * lg1, 0);
	//printf("Am primit sirul %s cu %d\n", sir1,octsir1);

	uint16_t lg2;
        recv(c, &lg2, sizeof(int), 0);
        lg2 = ntohs(lg2);
	char* sir2 = (char*)malloc(sizeof(char) * lg2);
        recv(c, sir2, sizeof(char) * lg2, 0);
	//printf("Am primit %hu\n", lg2);
	//fflush(stdout);

	int lginter = lg1 + lg2 +1;
        char* sirinter = (char*)malloc(sizeof(char) * lginter);
	int i = 0, j = 0, k = 0;
	while (i < lg1 && j < lg2) {
		if (sir1[i] <= sir2[j])	{
			sirinter[k++] = sir1[i++];
		}
		else {
			sirinter[k++] = sir2[j++];
		}
	}

	while (i < lg1) {
		sirinter[k++] = sir1[i++];
	}

	while (j < lg2) {
                sirinter[k++] = sir2[j++];
        }
	printf("Sir : %s", sirinter);
	sirinter[k++] = '\0';
	uint16_t lg = strlen(sirinter);
	lg = htons(lg);
	send(c, &lg, sizeof(uint16_t), 0);
	lg = ntohs(lg);
        send(c, sirinter, sizeof(char)*lg, 0);
        free(sir1);
	free(sir2);
        free(sirinter);
        close(c);
}

int main() {
        int s, c, l;
        struct sockaddr_in server, client;

        s = socket(AF_INET, SOCK_STREAM, 0);
        if (s < 0) {
                printf("Eroare la crearea socketului server!\n");
                return 1;
        }

        memset(&server, 0, sizeof(server));
        server.sin_port = htons(1234);
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;

        if (bind(s, (struct sockaddr*) &server, sizeof(server)) < 0) {
                printf("Eroare la bind!\n");
                return 1;
        }

        listen(s, 5);
        l = sizeof(client);

        memset(&client, 0, sizeof(client));
        while(1) {
                c = accept(s, (struct sockaddr*) &client, &l);
                printf("S-a conectat un client.\n");

                deservireclient(c);
        }

}
