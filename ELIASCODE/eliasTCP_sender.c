/* Prof. Elias P. Duarte Jr.
   Um Cliente TCP/IP
   Ultima Atualizacao: 07/11/2024 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {  
    int sockdescr;
    int numbytesrecv;
    struct sockaddr_in enderec_servidor;
    struct hostent *hp;
    char buf[BUFSIZ+1];
    char *host;
    char *dados;

    if(argc != 4) {
      puts("Uso correto: cliente <nome-servidor> <porta> <dados>");
      exit(1);
    }

    host = argv[1];
    dados = argv[3];

    // DONE:

    if((hp = gethostbyname(host)) == NULL){
      puts("Nao consegui obter endereco IP do servidor.");
      exit(1);
    }

    // DONE:

    bcopy((char *)hp->h_addr, (char *)&enderec_servidor.sin_addr, hp->h_length);

    enderec_servidor.sin_family = AF_INET;

    enderec_servidor.sin_port = htons(atoi(argv[2]));

    if((sockdescr=socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      puts("Nao consegui abrir o socket.");
      exit(1);
    }

    // DONE:

    if(connect(sockdescr, (struct sockaddr *) &enderec_servidor, sizeof enderec_servidor) < 0) {
      puts("Nao consegui conectar ao servidor");
      exit(1);
    }

    // DONE: BELOW IS FUNCTIONALITY, ABOVE IS CONFIGURATION

    if(write(sockdescr, dados, strlen(dados)) != strlen(dados)){
      puts("Nao consegui mandar os dados"); 
      exit(1);
    }

    read(sockdescr, buf, BUFSIZ);
    printf("Sou o cliente, recebi: %s\n", buf);
   
    close(sockdescr);
    exit(0);
}
