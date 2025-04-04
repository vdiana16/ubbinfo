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
    uint16_t lgsir;
    
    // 1. Primim lungimea șirului (uint16_t în format de rețea - Big Endian)
    recv(c, &lgsir, sizeof(uint16_t), 0);
    lgsir = ntohs(lgsir);  // Convertim la formatul gazdei (Little Endian)
    printf("Am primit lg sir: %hu\n", lgsir);

    // 2. Alocăm spațiu pentru șirul primit și citim șirul de caractere
    char* sir = (char*)malloc(lgsir + 1);  // +1 pentru terminatorul NULL
    int k = recv(c, sir, lgsir, MSG_WAITALL);
    sir[lgsir] = '\0';  // Asigurăm terminatorul NULL pentru afișare corectă
    printf("Numarul de bytes primiti este: %d\n", k);
    printf("Sirul: %s\n", sir);

    // 3. Calculăm numărul de spații goale în șir
    uint16_t contor = 0;
    for (int i = 0; i < lgsir; i++) {
        if (sir[i] == ' ') {
            contor++;
        }
    }
    printf("Numarul de spatii goale este: %hu\n", contor);

    // 4. Trimitem rezultatul (numărul de spații goale) înapoi în format de rețea
    contor = htons(contor);  // Convertim la format de rețea (Big Endian)
    send(c, &contor, sizeof(uint16_t), 0);

    // 5. Eliberăm memoria și închidem conexiunea cu clientul
    free(sir);
    close(c);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Eroare! Mod utilizare: ./server port_number\n");
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
        c = accept(s, (struct sockaddr *) &server, &l);
        printf("S-a conectat un client.\n");
        if (fork() == 0) {
            deservire_client(c);
            printf("Client deconectat.\n");
            return 0;
        }
    }
    close(s);
}

