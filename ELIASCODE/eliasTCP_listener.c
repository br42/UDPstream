/* Prof. Elias P. Duarte Jr.
   Um Servidor TCP/IP Iterativo
   Ultima Atualizacao: 07/11/2024 */

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define TAMFILA      5
#define MAXHOSTNAME 30

int main (int argc, char *argv[]) {
	int sock_escuta, sock_atende;
	int i;
    char buf [BUFSIZ + 1];
	struct sockaddr_in enderec_local, enderec_cliente;
	struct hostent *hp;
	char localhost [MAXHOSTNAME];

    if (argc != 2) {
       puts("Uso correto: servidor <porta>");
       exit(1);
    }

	// DONE:

	gethostname(localhost, MAXHOSTNAME);

	if ((hp = gethostbyname( localhost)) == NULL){
		puts ("Nao consegui meu proprio IP");
		exit (1);
	}

	// DONE:
	
	enderec_local.sin_port = htons(atoi(argv[1]));

	bcopy ((char *) hp->h_addr, (char *) &enderec_local.sin_addr, hp->h_length);

	enderec_local.sin_family = AF_INET;

	if ((sock_escuta = socket(AF_INET, SOCK_STREAM, 0)) < 0){
           puts ( "Nao consegui abrir o socket" );
		exit (1);
	}

	// DONE:

	if (bind(sock_escuta, (struct sockaddr *) &enderec_local, sizeof(enderec_local)) < 0){
		puts ( "Nao consegui fazer o bind" );
		exit (1);
	}
 
	listen (sock_escuta, TAMFILA);

	// DONE: BELOW IS FUNCTIONALITY, ABOVE IS CONFIGURATION	
	
	while (1){
		i = sizeof(enderec_local);
		if ((sock_atende=accept(sock_escuta, (struct sockaddr *) &enderec_cliente, &i))<0){
                   puts ( "Nao consegui estabelecer conexao" );
                   exit (1);
		}	

       read(sock_atende, buf, BUFSIZ);
       printf("Sou o servidor, recebi a mensagem----> %s\n", buf);
       write(sock_atende, buf, BUFSIZ);
       close(sock_atende);
   }


   exit(0);
}
