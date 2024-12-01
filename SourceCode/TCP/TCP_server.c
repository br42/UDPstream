#include "../../runner.h"



//--------------------------------------



// prepares socket to be a TCP listener
// returns 1 for success and 0 for error
int tsvr_prep_listener_socket(socket_listener_info* sckt) {
    
    if (listen(sckt->socket_identifier, MAXFILA) < 0) {
        fprintf(stderr, "ERRO, ao iniciar comunicacao\n");
        return 0;
    }
    
    //--

    return 1;
}



//--------------------------------------



// Accept a connection request
// return 1 for success, 0 for error
int tsvr_accept_listener(socket_listener_info* sckt) {
    int siz = sizeof(sckt->socket_info);

    //--

    fprintf(stderr, "Preparando para aceitar conexao...\n");

    sckt->listener_identifier = accept(sckt->socket_identifier, (struct sockaddr *) &sckt->listener_socket_info, &siz);

    if (sckt->listener_identifier < 0) {
        fprintf(stderr, "ERRO, falha ao aceitar conexao\n");
        return 0;
    }

    fprintf(stderr, "Pedido de conexao aceito\n");

    //--

    return 1;
}


// close listener connection
// return 1 for success, 0 for error
int tsvr_stop_listening(socket_listener_info* sckt) {
    if (sckt->listener_identifier == 0) {
        fprintf(stderr, "ERRO: fechando listener nao existente\n");
        return 0;
    }
    
    //--

    close(sckt->listener_identifier);
    return 1;
}


// read 1 message from listener socket
// return the size of the message
int tsvr_receive_message(socket_listener_info* sckt) {

    fprintf(stderr, "Recebendo mensagem...\n");

    int recvBytes = read(sckt->listener_identifier, sckt->buffer, BUFSIZ);
    
    fprintf(stderr, "   Recebido %d bytes\n", recvBytes);

    //--

    return recvBytes;
}



//--------------------------------------