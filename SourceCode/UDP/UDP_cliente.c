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



// sends 1-1-1 to the server stating as the last message
// will wait for a response and resend if needed
float uclt_send_FIM_message(socket_sender_info* sckt) {
    if (sckt == NULL) {
        fprintf(stderr, "ERRO: Scoket nao existente\n");
        return 0;
    }

    //// ==== set buffer as FIM message

    sckt->buffer[0] = 1;
    sckt->buffer[1] = 1;
    sckt->buffer[2] = 1;

    //// ==== Send the message

    fprintf(stderr, "Enviando FIM...\n");

    int msgSent = sendto(sckt->socket_identifier, sckt->buffer, 3, MSG_DONTWAIT, (struct sockaddr *) &sckt->socket_info, sizeof(sckt->socket_info));

    //// ==== verify if error

    if (msgSent != 3) {
        fprintf(stderr, "Erro ao enviar mensagem, erro: %s\n", strerror(errno));
        return -1;
    }

    //// ==== 

    return 0;
}


// fill buffer and send 1 message to server
// msgSize is the amount in bytes of data to transfer
// return the time it took to send or negative for error
int uclt_send_message(socket_sender_info* sckt, int msgSize) {

    if (sckt == NULL) {
        fprintf(stderr, "ERRO: Scoket nao existente\n");
        return 0;
    }

    //// ==== fill the buffer with data
    
    socket_fill_buffer(sckt, msgSize);

    //// ==== send the message

    fprintf(stderr, "Enviando %d bytes de dados...\n", msgSize);

    int msgSent = sendto(sckt->socket_identifier, sckt->buffer, msgSize, MSG_DONTWAIT, (struct sockaddr *) &sckt->socket_info, sizeof(sckt->socket_info));

    //// ==== verify if error

    if (msgSent != msgSize) {
        fprintf(stderr, "Erro ao enviar mensagem, erro: %s\n", strerror(errno));
        return -1;
    }

    //// ==== return the time the message took

    return 0;
}