#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

void deservire_client(int c){
        //deservirea clientului
	uint16_t suma=0;
	while (1){
		uint16_t num;
		recv(c, &num, sizeof(uint16_t), MSG_WAITALL);
		num = ntohs(num);
		suma += num;
		if (num == 0)
			break;
	}
	printf("Suma totala este %hu\n", suma);
	suma = htons(suma);
	send(c, &suma, sizeof(uint16_t), 0);
      	//sfarsitul deservirii clientului
}


int main(int argc, char* argv[]){
        if(argc < 2) {
                printf("Eroare! Mod utilizare: ./server port_number\n");
                return 1;
        }

        int s, c, l;
        struct sockaddr_in server, client;

        //creez socketul pentru server
        s = socket(AF_INET, SOCK_STREAM, 0);
        if (s < 0) {
                printf("Eroare la crearea socketului server\n");
                return 1;
        }

	//initializez serverul cu informatiile utile
        memset(&server, 0, sizeof(server));
        server.sin_port = htons(atoi(argv[1]));
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;

        //fac disponibil serverul
        if (bind(s, (struct sockaddr*) &server, sizeof(server)) < 0){
                printf("Eroare la bind\n");
                return 1;
        }

        //creez coada de asteptare
        listen(s, 5);
        l = sizeof(client);

	//initializez clientul
        memset(&client, 0, sizeof(server));
        while (1){
                //accept clientul
                c = accept(s, (struct sockaddr*) &client, &l);
                printf("S-a conectat un client.\n");
                if (fork() == 0) {
                        deservire_client(c);
                        return 0;
                }
        }
}
