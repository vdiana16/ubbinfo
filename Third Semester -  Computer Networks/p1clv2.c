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

#define CAPACITY 1024
#define CAPACITY2 350

//Un client trimite unui server un sir de numere. Serverul va returna clientului suma numerelor
//primite

int main(int argc,char* argv[]){
        if (argc < 2){
                printf("Ai uitat de port!\n");
                return 1;
        }

        int c;
        struct sockaddr_in server;

        //creez socket-ul
        c = socket(AF_INET, SOCK_STREAM, 0);
        if (c < 0){
                printf("Eroare la crearea socketului client\n");
                return 1;
        }

	//initializez informatiile utile pentru server
        memset(&server, 0, sizeof(server));
        server.sin_port = htons(atoi(argv[1]));
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr("127.0.0.1");

        //realizez conectarea la server
        if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0){
                printf("Eroare la conectarea la server\n");
                return 1;
        }

        //primesc datele
	printf("Introduceti numerele sau 0 pentru a termina sirul de numere: ");
	while(1){
		uint16_t num;
		scanf("%hu", &num);
		num = htons(num);
        	send(c, &num, sizeof(uint16_t), 0);
        	if(num == 0){
			break;
		}
	}
        printf("Numere trimise cu succes!\n");

        //primesc rezultatul
        uint16_t suma;
        recv(c, &suma, sizeof(suma), 0);
        suma = ntohs(suma);
        printf("Suma numerelor este %hu\n", suma);

        //inchid socketul client
        close(c);
}
