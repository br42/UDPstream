#include "../../runner.h"



//--------------------------------------

network_info netInfo;

//--------------------------------------

/*
    This file is responsible for all socket manipulations and functions.
*/

//--------------------------------------



// required initial preparation to use the network
void sck_network_prep() {
    gethostname(netInfo.host_name, 64);
    fprintf(stderr, "DEBUG:: Nome dessa maquina: %s\n", netInfo.host_name);
}



//--------------------------------------



// Create and opens a sender-socket.
// socket_type: is either SOCK_STREAM for TCP | SOCK_DGRAM for UDP
// host: the server name to send messages to
// port: the number of the port this socket opens
socket_sender_info* socket_create_sender(char* host, int socket_type) {

    //// ==== Alloc memory for the socket

    socket_sender_info* sckt = malloc(sizeof(socket_sender_info));
    if (sckt == NULL) {
        fprintf(stderr, "ERRO, ao criar socket\n");
        return NULL;
    }

    bzero(&sckt->socket_info, sizeof(sckt->socket_info));

    //// ==== Get server IP via parameter

    fprintf(stderr, "DEBUG:: tentando achar %s\n", host);

    struct hostent* hp = gethostbyname(host);
    if (hp == NULL) {
		fprintf(stderr, "ERRO, IP do host desse socket nao localizado\n");
        free(sckt);
		return 0;
	}

    fprintf(stderr, "DEBUG:: NOME do servidor %s\n", hp->h_name);
    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, hp->h_addr_list[0], str, INET_ADDRSTRLEN);
    fprintf(stderr, "DEBUG:: IP do servidor %s\n", str);

    //// ==== Set basic variables

    sckt->socket_info.sin_port = htons(PORT);                                                       // Get PORT to use
    sckt->socket_info.sin_family = AF_INET;                                                         // Always AF_INET == IPv4 Adress use
    sckt->socket_info.sin_addr = *((struct in_addr *) hp->h_addr_list[0]);                          // Set server IP

    //// ==== Create socket sender identifier

    sckt->socket_identifier = socket(AF_INET, socket_type, 0);
    if (sckt->socket_identifier < 0) {
        fprintf(stderr, "ERRO, ao tentar abrir o socket\n");
        free(sckt);
		return NULL;
	}

    //// ==== return the created socket

    return sckt;
}



//--------------------------------------



// Create and opens a listener-socket.
// socket_type: is either SOCK_STREAM for TCP | SOCK_DGRAM for UDP
// port: the number of the port this socket opens
socket_listener_info* socket_create_listener(int socket_type) {

    //// ==== Alloc memory for the socket

    socket_listener_info* sckt = malloc(sizeof(socket_listener_info));
    if (sckt == NULL) {
        fprintf(stderr, "ERRO, ao criar socket\n");
        return NULL;
    }

    bzero(&sckt->socket_info, sizeof(sckt->socket_info));

    //// ==== Set server-IP via this machine's name

    //struct hostent* hp = gethostbyname(netInfo.host_name);    //DEBUG:
    struct hostent* hp = gethostbyname(LOOPBACK);
    if (hp == NULL) {
		fprintf(stderr, "ERRO, host que deveria ser essa maquina nao encontrado\n");
        free(sckt);
		return 0;
	}

    fprintf(stderr, "DEBUG:: NOME dessa maquina %s\n", hp->h_name);
    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, hp->h_addr_list[0], str, INET_ADDRSTRLEN);
    fprintf(stderr, "DEBUG:: IP dessa maquina %s\n", str);

    //// ==== Set basic variables

    sckt->socket_info.sin_port = htons(PORT);                                                       // Get PORT to use
    sckt->socket_info.sin_family = AF_INET;                                                         // Always AF_INET == IPv4 Adress use
    sckt->socket_info.sin_addr = *((struct in_addr *) hp->h_addr_list[0]);          // Set server IP

    //// ==== Obtain socket listener identifier

    sckt->socket_identifier = socket(AF_INET, socket_type, 0);
    if (sckt->socket_identifier < 0) {
        fprintf(stderr, "ERRO, ao tentar abrir o socket\n");
        free(sckt);
		return NULL;
	}

    //// ==== Bind port to the listener socket

    int erro = bind(sckt->socket_identifier, (struct sockaddr *) &sckt->socket_info, sizeof(sckt->socket_info));
    if (erro < 0) {
		fprintf(stderr, "ERRO: falha ao bindar canal de escuta\n");
        free(sckt);
		return 0;
	}

    //// ==== Return the created and configured socket

    return sckt;
}


//--------------------------------------



// necessary functions to properly close a sender-socket
void socket_close_sender(socket_sender_info* sckt) {
    close(sckt->socket_identifier);

    //--

    free(sckt);
}


// necessary functions to properly close a listener-socket
void socket_close_listener(socket_listener_info* sckt) {
    close(sckt->socket_identifier);

    //--

    free(sckt);
}



//--------------------------------------



// fill a buffer up to the size determined
void socket_fill_buffer(socket_sender_info* sckt, unsigned long sizeToFill) {

    for (unsigned long i = 0; i < 4*(sizeToFill/4ul); i += 4) {
        sckt->buffer[i]   = (( i ) % 255);
        sckt->buffer[i+1] = ((i+1) % 255);
        sckt->buffer[i+2] = ((i+2) % 255);
        sckt->buffer[i+3] = ((i+3) % 255);
    }

    for (unsigned long i = 4*(sizeToFill/4ul); i < sizeToFill; i++) {
        sckt->buffer[i]   = (( i ) % 255);
    }

    return;

}



//--------------------------------------