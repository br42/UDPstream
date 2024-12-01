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



// FOR INTERNAL USE ONLY
// returns 0 if this is not the last message, 1 otherwise
int verify_last(unsigned char* buffer, int size) {
    if (size != 3) {
        return 0;
    }

    //--

    if ((buffer[0] == 1) && (buffer[1] == 1) && (buffer[2] == 1)) {
        fprintf(stderr, "Detectado mensagem de FIM\n");
        return 1;
    }

    //--

    return 0;
}



//--------------------------------------



// receive 1 message from the internet
// returns negative msgSize if this is the last message
int usvr_receive_message(socket_listener_info* sckt) {

    if (sckt == NULL) {
        fprintf(stderr, "ERRO: Socket nao existente\n");
        return 0;
    }

    //// ==== receive a message

    int siz = sizeof(sckt->socket_info);

    //--

    fprintf(stderr, "Esperando mensagem...\n");
    int rcvSize = recvfrom(sckt->socket_identifier, sckt->buffer, BUFSIZ, 0, (struct sockaddr*) &sckt->listener_socket_info, &siz);
    fprintf(stderr, "   %d bytes recebidos do cliente...\n", rcvSize);

    if (rcvSize < 0) {
        fprintf(stderr, "ERRO:: ao ler do socket, erro: %s\n", strerror(errno));
        return rcvSize;
    }

    //// ==== verify if this is the last message by the client

    if (verify_last(sckt->buffer, rcvSize)) {
        return (-rcvSize);
    }

    //// ==== verify if there was package lost

    socket_compare_sequence(sckt->buffer[0]);

    //// ==== return the amount of bytes received

    return rcvSize;
}