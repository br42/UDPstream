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
// read messages until stop receiving them
// close connection
// return 1 for success, 0 for error
int tsvr_receive_message(socket_listener_info* sckt) {
    int siz = sizeof(sckt->socket_info);

    //--

    fprintf(stderr, "Preparando para aceitar conexao...\n");

    int sckt_listening = accept(sckt->socket_identifier, (struct sockaddr *) &sckt->listener_socket_info, &siz);

    if (sckt_listening < 0) {
        fprintf(stderr, "ERRO, falha ao aceitar conexao\n");
        return 0;
    }

    fprintf(stderr, "Pedido de conexao aceito\n");

    //--

    int numbytes = 0, recvbytes = 1;

    fprintf(stderr, "Recebendo mensagem...\n");

    while(recvbytes) {
        recvbytes = read(sckt_listening, sckt->buffer + numbytes, (numbytes>BUFSIZ) ? 0 : BUFSIZ-numbytes);
        numbytes += recvbytes;
        //fprintf(stderr, "   Recebido %d bytes\n", numbytes);
    }
    fprintf(stderr, "   Recebido %d bytes\n", numbytes);
    
    fprintf(stderr, "Acabou as mensagens, encerrando conexao\n");

    //--

    close(sckt_listening);
    return 1;
}



//--------------------------------------