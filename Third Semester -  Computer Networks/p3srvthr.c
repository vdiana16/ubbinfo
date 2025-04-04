#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

void* deservire_client(void* arg) {
        int c = *((int*)arg);
	free(arg);

	uint16_t lgsir;
        recv(c, &lgsir, sizeof(uint16_t), 0);
        lgsir = ntohs(lgsir);
        printf("Am primit lg sir: %hu\n", lgsir);

        char* sir = (char*)malloc(sizeof(char)*1024);
        int k = recv(c, sir, lgsir, MSG_WAITALL);
        printf("Numarul de bytes primiti este: %d\n", k);

        char* oglindit = (char*)malloc(sizeof(char)*1024);
        int j = 0;
        for(int i = lgsir - 2; i >= 0; i--) {
                oglindit[j++] = sir[i];
        }
        int m = send(c, oglindit, lgsir, 0);
        printf("Numarul de bytes trimisi este: %d\n", m);

        free(oglindit);
        free(sir);
        close(c);

	pthread_exit(NULL);
	return NULL;
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
                int c = accept(s, (struct sockaddr *) &server, &l);
                if (c < 0) {
			printf("Eroare la acceptare client\n");
                        continue;
		}

		printf("S-a conectat un client.\n");
             	int* client = malloc(sizeof(int));
		*client = c;
		pthread_t th;
		if (pthread_create(&th, NULL, deservire_client, client) != 0) {
			printf("Eroare la crearea threadului!\n");
			free(client);
                }
		else {
			pthread_detach(th);
		}
        }
}
