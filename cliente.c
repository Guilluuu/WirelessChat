#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_SIZE 500
#define PUERTO 5001 // Necesariamente tiene que ser mayor a IPPORT_RESERVED
int main() {
  int sock_cl, bytes_received;
  struct sockaddr_in IP_cl; // Especificaremos las direcciones que vamos a usar
  socklen_t size = sizeof(struct sockaddr_in); // para el tamaño
  char mensaje[MAX_SIZE];
  // Creación servidor
  sock_cl = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_cl < 0) {
    perror("No se ha podido asignar un socket\n");
    exit(2);
  }

  inet_pton(AF_INET, "127.0.0.1", &IP_cl.sin_addr);
  IP_cl.sin_family = AF_INET;
  IP_cl.sin_port = htons(PUERTO);

  if (connect(sock_cl, (struct sockaddr *)&IP_cl, size) < 0) {
    perror("No se pudo asignar la dirección\n");
    exit(3);
  }

  if (((bytes_received = recv(sock_cl, mensaje, size, 0)) < 0)) {
    perror("No se pudo enviar el mensaje\n");
    exit(5);
  }
  fflush(stdin);
  printf("%s", mensaje);
  printf("Numero de bytes recibidos: %d\n", bytes_received);

  /*fflush(stdin);
  printf("[>]: ");
  fgets(mensaje, MAX_SIZE, stdin);
  if (inet_ntop(AF_INET, (const void *)&IP_cl.sin_addr, IP_cl_texto,
                INET_ADDRSTRLEN) == NULL) {
    perror("Error imprimiendo la IP\n");
    exit(6);
  }

  printf("La dirección del cliente que se conectó es: %s\n", IP_cl_texto);
  printf("La dirección del puerto es: %d\n", IP_cl.sin_port);
  if ((bytes_sent = send(sock_conect, mensaje, strlen(mensaje), 0)) < 0) {
    perror("Error al enviar el mensaje\n");
    exit(6);
  }*/
  close(sock_cl);
  return 0;
}
