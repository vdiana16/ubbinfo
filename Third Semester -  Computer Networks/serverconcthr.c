#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include<pthread.h>


void * socketThread(void *arg)
{
    printf("Deservice client...\n");
    uint16_t a, b, suma;
    int newSocket = *((int *)arg);
    recv(newSocket, &a, sizeof(a), MSG_WAITALL);
    recv(newSocket, &b, sizeof(b), MSG_WAITALL);
    a = ntohs(a);
    b = ntohs(b);
    suma = a + b;
    suma = htons(suma);
    send(newSocket, &suma, sizeof(suma), 0);

    close(newSocket);
    pthread_exit(NULL);
}

int main() {
    int s;
    struct sockaddr_in server, client;
    int c, l;

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        printf("Eroare la crearea socketului server\n");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("Eroare la bind\n");
        return 1;
    }

    listen(s, 5);

    l = sizeof(client);
    memset(&client, 0, sizeof(client));

    pthread_t tid[40];
    int i = 0;

    while (1) {
        c = accept(s, (struct sockaddr *) &client, &l);
        printf("S-a conectat un client.\n");

        if( pthread_create(&tid[i++], NULL, socketThread, &c) != 0 ) {
            printf("Failed to create thread\n");
        }
        if( i >= 30) {
            i = 0;
            while(i < 30) {
                pthread_join(tid[i++],NULL);
            }
            i = 0;
        }

    }
}
