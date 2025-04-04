#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX_CLIENTS 100

void *deservire_client(void *arg) {
  int c = *((int *)arg);
  free(arg);

  uint16_t a, b, suma;
  recv(c, &a, sizeof(a), MSG_WAITALL);
  recv(c, &b, sizeof(b), MSG_WAITALL);
  a = ntohs(a);
  b = ntohs(b);
  suma = a + b;
  suma = htons(suma);
  send(c, &suma, sizeof(suma), 0);
  close(c);
  return NULL;
}

int main() {
  int s;
  struct sockaddr_in server, client;
  int l;

  pthread_t threads[MAX_CLIENTS];
  int thread_count = 0;

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

  while (1) {
    int *c = malloc(sizeof(int));
    *c = accept(s, (struct sockaddr *) &client, &l);
    if (*c < 0) {
      printf("Eroare la acceptare\n");
      free(c);
      continue;
    }
    printf("S-a conectat un client.\n");

    if (pthread_create(&threads[thread_count], NULL, deservire_client, c) != 0) {
      printf("Eroare la crearea thread-ului\n");
      free(c);
    } else {
      thread_count++;
    }

   for (int i=0; i< thread_count; i++) {
     pthread_join(threads[i], NULL);
   }
   thread_count = 0;
  }

  close(s);
  return 0;
}


