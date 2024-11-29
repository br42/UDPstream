#include "../../runner.h"



//--------------------------------------



// prepares socket to be a TCP listener
// returns 1 for sucess and 0 for error
int tsvr_prep_listener_socket(socket_listener_info* sckt) {
    
    if (listen(sckt->socket_identifier, MAXFILA) < 0) {
        fprintf(stderr, "ERRO, ao iniciar comunicacao\n");
        return 0;
    }
    
    //--

    return 1;
}



//--------------------------------------



// allow socket-listener to accept a single connection
// return 1 for sucess, 0 for error
int tsvr_receive_message(socket_listener_info* sckt) {
    int siz = sizeof(sckt->socket_info);

    //--

    int sckt_listening = accept(sckt->socket_identifier, (struct sockaddr *) &sckt->listener_socket_info, &siz);

    if (sckt_listening < 0) {
        fprintf(stderr, "ERRO, falha ao aceitar conexao\n");
        return 0;
    }

    //--

    int numbytes = 1;

    while(numbytes) {
        numbytes = read(sckt_listening, sckt->buffer, BUFSIZ);
    }

    //--

    return 1;
}



//--------------------------------------