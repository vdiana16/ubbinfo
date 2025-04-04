#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

void deservire_client(int c) {
    // Primesc primul sir
    uint16_t lgs1;
    recv(c, &lgs1, sizeof(uint16_t), 0);
    lgs1 = ntohs(lgs1);
    printf("Am primit lg sir 1: %hu\n", lgs1);

    uint16_t* s1 = (uint16_t*)malloc(sizeof(uint16_t) * lgs1);
    int k1 = recv(c, s1, sizeof(uint16_t) * lgs1, MSG_WAITALL);
    printf("Numarul de bytes primiti pentru sir 1: %d\n", k1);

    // Primesc al doilea sir
    uint16_t lgs2;
    recv(c, &lgs2, sizeof(uint16_t), 0);
    lgs2 = ntohs(lgs2);
    printf("Am primit lg sir 2: %hu\n", lgs2);

    uint16_t* s2 = (uint16_t*)malloc(sizeof(uint16_t) * lgs2);
    int k2 = recv(c, s2, sizeof(uint16_t) * lgs2, MSG_WAITALL);
    printf("Numarul de bytes primiti pentru sir 2: %d\n", k2);

    uint16_t lgs3 = 0;
    uint16_t* s3 = (uint16_t*)malloc(sizeof(uint16_t) * (lgs1 < lgs2 ? lgs1 : lgs2)); // Buffer optimizat

    // Caut numerele comune
    for (int i = 0; i < lgs1; i++) {
        for (int j = 0; j < lgs2; j++) {
            if (s1[i] == s2[j]) {
                s3[lgs3] = s1[i]; // Conversia pentru rețea
                lgs3++;
                break;
            }
        }
    }

    // Trimite lungimea sirului rezultat
    lgs3 = htons(lgs3);
    send(c, &lgs3, sizeof(uint16_t), 0);
    
    // Trimite numerele comune
    if (ntohs(lgs3) > 0) { // Verificam daca avem numere de trimis
        send(c, s3, sizeof(uint16_t) * ntohs(lgs3), 0);
    }

    // Afisam numerele trimise
    printf("Numerele comune trimise: ");
    for (int i = 0; i < ntohs(lgs3); i++) {
        printf("%hu ", ntohs(s3[i]));
    }
    printf("\n");

    // Curățare
    free(s3);
    free(s2);
    free(s1);
    close(c);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Eroare! Mod utilizare: ./server port_number");
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

    if (bind(s, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("Eroare la bind\n");
        return 1;
    }

    listen(s, 5);
    l = sizeof(client);
    memset(&client, 0, sizeof(server));
    while (1) {
        c = accept(s, (struct sockaddr*)&server, &l);
        printf("S-a conectat un client.\n");
        if (fork() == 0) {
            deservire_client(c);
            printf("Client deconectat.\n");
            return 0;
        }
    }
}

