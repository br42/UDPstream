#include "../../runner.h"



//--------------------------------------



// prepares socket to be a UDP listener
// returns 1 for success and 0 for error
int usvr_prep_listener_socket(socket_listener_info* sckt) {

    if (sckt == NULL) {
        fprintf(stderr, "ERRO: Preparando um socket nao existente\n");
        return 0;
    }

    //--

    // UDP does not need any preparation to receive messages
    return 1;
}



//--------------------------------------



// receive a message from the internet
int usvr_receive_message(socket_listener_info* sckt) {

    if (sckt == NULL) {
        fprintf(stderr, "ERRO: Socket nao existente\n");
        return 0;
    }

    //--

    int siz = sizeof(sckt->socket_info);

    //--

    fprintf(stderr, "Esperando mensagem...\n");

    int msgReceived = recvfrom(sckt->socket_identifier, sckt->buffer, BUFSIZ, 0, (struct sockaddr*) &sckt->listener_socket_info, &siz);

    fprintf(stderr, "%d bytes recebidos de cliente\n", siz);

    //--

    return msgReceived;
}