#include "../runner.h"



//--------------------------------------



// prepares socket to be a TCP listener
// returns 1 for sucess and 0 for error
int tcp_prepare_listener_socket(socket_listener_info* sckt, int maxConnections) {
    
    if (listen(sckt->socket_identifier, maxConnections) < 0) {
        fprintf(stderr, "ERRO, ao iniciar comunicacao\n");
        return 0;
    }
    
    //--

    return 1;
}


// prepares socket to be a TCP sender
// returns 1 for sucess and 0 for error
int tcp_prepare_sender_socket(socket_sender_info* sckt) {

    if(connect(sckt->socket_identifier, (struct sockaddr *) &sckt->socket_info, sizeof(sckt->socket_info)) < 0) {
      puts("ERRO: falha ao connectar a algum servidor\n");
      return 0;
    }

    //--

    return 1;
}