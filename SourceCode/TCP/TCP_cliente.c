#include "../../runner.h"



//--------------------------------------



// prepares socket to be a TCP sender
// returns 1 for success and 0 for error
int tclt_prep_sender_socket(socket_sender_info* sckt) {

    if(connect(sckt->socket_identifier, (struct sockaddr *) &sckt->socket_info, sizeof(sckt->socket_info)) < 0) {
      puts("ERRO: falha ao connectar a algum servidor\n");
      return 0;
    }

    //--

    int valtrue = 1;
    if(setsockopt(sckt->socket_identifier, IPPROTO_TCP, TCP_NODELAY, &valtrue, sizeof(valtrue)) < 0) {
      fprintf(stderr, "ERRO: Nao foi possivel definir opcoes para o socket\n");
    }

    return 1;
}



//--------------------------------------



// Send 1 message to server
// return the time it took to send or negative for error
float tclt_send_message(socket_sender_info* sckt, int msgSize) {

    if (sckt == NULL) {
        fprintf(stderr, "ERRO: Scoket nao existente\n");
        return -1.0f;
    }

    //--
    
    socket_fill_buffer(sckt, msgSize);

    //--

    fprintf(stderr, "Enviando %d bytes de dados...\n", msgSize);

    float tStart = clock();       // get the time start
    int msgSent = sendto(sckt->socket_identifier, sckt->buffer, msgSize, MSG_DONTWAIT, (struct sockaddr *) NULL, 0);
    float tEnd = clock();

    //--

    if (msgSent != msgSize) {
        return -2.0f;
    }

    //--

    return ((tEnd - tStart) / CLOCKS_PER_SEC);
    //return 1;
}



//--------------------------------------