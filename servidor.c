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
  int sock_serv, sock_conect, bytes_sent;
  struct sockaddr_in IP_serv,
      IP_cl; // Especificaremos las direcciones que vamos a usar
  socklen_t size = sizeof(struct sockaddr_in); // para el tamaño
  char mensaje[MAX_SIZE] = ("Soy un mensaje\n"), IP_cl_texto[INET_ADDRSTRLEN];
  // Creación servidor
  sock_serv = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_serv < 0) {
    perror("No se ha podido asignar un socket\n");
    exit(2);
  }

  IP_serv.sin_addr.s_addr = htonl(INADDR_ANY);
  IP_serv.sin_family = AF_INET;
  IP_serv.sin_port = htons(PUERTO);

  if (bind(sock_serv, (struct sockaddr *)&IP_serv, size) < 0) {
    perror("No se pudo asignar la dirección\n");
    exit(3);
  }

  if (listen(sock_serv, 2) < 0) {
    perror("Error listen\n");
    exit(4);
  }
  while (1) {
    if ((sock_conect = accept(sock_serv, (struct sockaddr *)&IP_cl, &size)) <
        0) {

      perror("No se pudo aceptar la conexion");
      exit(5);
    }

    fflush(stdin);
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
    }
    printf("Numero de bytes impresos: %d\n", bytes_sent);
    close(sock_conect);
  }
  close(sock_serv);
  return 0;
}
