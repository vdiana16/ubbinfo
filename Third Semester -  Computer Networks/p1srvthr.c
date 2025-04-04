#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#define STRING_SIZE 1024

void* deservire_client(void* arg) {
    	int c = *((int*)arg);    // preiau socketul din argument
   	free(arg);

	//deservirea clientului
        uint16_t lg;
        recv(c, &lg, sizeof(lg), MSG_WAITALL);
        lg = ntohs(lg);
        uint16_t* nr = (uint16_t*)malloc(sizeof(uint16_t) * lg);
        recv(c, nr, sizeof(uint16_t) * lg, MSG_WAITALL);

        uint16_t suma = 0;
        for (int i = 0; i < lg; i++){
                suma += ntohs(nr[i]);
        }

        printf("Suma %hu\n", suma);
        printf("Trimitere suma \n");
        suma = htons(suma);
        send(c, &suma, sizeof(suma), 0);

        free(nr);
        printf("Suma trimisa cu succes!\n");
	close(c);
       	//sfarsitul deservirii clientului

	pthread_exit(NULL);  // Termin executia threadului curent
    	return NULL;
}

int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("Eroare! Mod utilizare: ./server port_number");
        return 1;
    }

    int s;
    struct sockaddr_in server, client;
    int l;

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
    memset(&client, 0, sizeof(client));

    while (1) {
        int c = accept(s, (struct sockaddr *) &client, &l);
        if (c < 0) {
            printf("Eroare la acceptare client\n");
            continue;
        }

        printf("[IN SERVER] S-a conectat un client.\n");

        // aloc memorie pentru socketul clientului pentru a-l putea trece la thread
        int* client_socket = malloc(sizeof(int));
        *client_socket = c;

        pthread_t th;
        // creez un thread pentru fiecare client
        if (pthread_create(&th, NULL, deservire_client, client_socket) != 0) {
            printf("Eroare la crearea threadului\n");
            free(client_socket);
        } else {
            // detach la thread pentru a rula independent, serverul nefiind nevoit sa astepte
            // finalizarea acestuia
            pthread_detach(th);
        }
    }

}
