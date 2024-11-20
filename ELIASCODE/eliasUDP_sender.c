/* Prof. Elias P. Duarte Jr. 
   Um Cliente UDP/IP
   Ultima atualizacao: 07/11/2024 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

main(int argc, char *argv[]) 

 {  int sockdescr;
    int numbytesrecv;
    struct sockaddr_in sa;
    struct hostent *hp;
    char buf[BUFSIZ+1];
    char *host;
    char *dados;

    unsigned int i;

    if(argc != 4) {
      puts("Uso correto: <cliente> <nome-servidor> <porta> <dados>");
      exit(1);
    }

    // DONE:

    host = argv[1];
    dados = argv[3];

    if((hp = gethostbyname(host)) == NULL){
      puts("Nao consegui obter endereco IP do servidor.");
      exit(1);
    }

    // DONE:

    bcopy((char *)hp->h_addr, (char *)&sa.sin_addr, hp->h_length);
    sa.sin_family = hp->h_addrtype;

    sa.sin_port = htons(atoi(argv[2]));

    // DONE:

    if((sockdescr=socket(hp->h_addrtype, SOCK_DGRAM, 0)) < 0) {
      puts("Nao consegui abrir o socket.");
      exit(1);
    }

    // DONE:

    if(sendto(sockdescr, dados, strlen(dados)+1, 0, (struct sockaddr *) &sa, sizeof sa) != strlen(dados)+1){
      puts("Nao consegui mandar os dados"); 
      exit(1);
    }

    recvfrom(sockdescr, buf, BUFSIZ, 0, (struct sockaddr *) &sa, &i);

    printf("Sou o cliente, recebi: %s\n", buf);
   
    close(sockdescr);
    exit(0);
}
