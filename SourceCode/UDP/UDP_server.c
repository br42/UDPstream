#include "../../runner.h"



//--------------------------------------



// prepares socket to be a UDP listener
// returns 1 for success and 0 for error
int usvr_prep_listener_socket(socket_listener_info* sckt) {

    // UDP does not need any preparation to receive messages
    return 1;
}



//--------------------------------------



// receive a message from the internet
int usvr_receive_message(socket_listener_info* sckt) {

    int sz = sizeof(sckt->socket_info);

    //--

    fprintf(stderr, "Esperando mensagem...\n");

    int msgReceived = recvfrom(sckt->socket_identifier, sckt->buffer, BUFSIZ, 0, (struct sockaddr*) &sckt->listener_socket_info, &sz);

    fprintf(stderr, "%d bytes recebidos de cliente\n", sz);

    //--

    return msgReceived;
}