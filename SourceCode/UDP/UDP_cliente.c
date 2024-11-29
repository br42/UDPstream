#include "../../runner.h"



//--------------------------------------



// prepares socket to be a UDP sender
// returns 1 for success and 0 for error
int uclt_prep_sender_socket(socket_sender_info* sckt) {

    if (sckt == NULL) {
        fprintf(stderr, "ERRO: Preparando um socket nao existente\n");
        return 0;
    }

    //--

    // UDP does not need any preparation for the sender machine
    return 1;
}



//--------------------------------------



// fill buffer and send message to server
// return the time it took to send or negative for error
float uclt_send_message(socket_sender_info* sckt, int msgSize) {

    if (sckt == NULL) {
        fprintf(stderr, "ERRO: Scoket nao existente\n");
        return 0;
    }

    //--
    
    socket_fill_buffer(sckt, msgSize);

    //--

    fprintf(stderr, "Enviando %d bytes de dados...\n", msgSize);

    float tStart = clock();       // get the time start
    int msgSent = sendto(sckt->socket_identifier, sckt->buffer, msgSize, 0, (struct sockaddr *) &sckt->socket_info, sizeof(sckt->socket_info));
    float tEnd = clock();

    //--

    if (msgSent != msgSize) {
        return -1;
    }

    fprintf(stderr, "Mensagem recebida pelo servidor\n");

    //--

    return ((tEnd - tStart) / CLOCKS_PER_SEC);
}