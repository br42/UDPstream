#include "../runner.h"



//--------------------------------------

network_info netInfo;

//--------------------------------------



// required initial preparation to use the network
void con_network_prep() {
    gethostname(netInfo.host_name, 64);
    fprintf(stderr, "DEBUGG:: Nome da maquina: %s\n", netInfo.host_name);
}



//--------------------------------------



// Create and opens a sender-socket.
// socket_type: is either SOCK_STREAM for TCP | SOCK_DGRAM for UDP
// host: the server name to send messages to
// port: the number of the port this socket opens
socket_sender_info* con_create_sender_socket(char* host, int socket_type, int port) {

    //// ==== 

    socket_sender_info* sckt = malloc(sizeof(socket_sender_info));
    if (sckt == NULL) {
        fprintf(stderr, "ERRO, ao criar socket\n");
        return NULL;
    }

    //// ====

    sckt->socket_info.sin_port = htons(port);
    sckt->socket_info.sin_family = AF_INET;     // Always AF_INET == IPv4 Adress use

    //// ====

    if ((sckt->socket_host = gethostbyname(host)) == NULL){
		fprintf(stderr, "ERRO, IP do host desse socket nao localizado\n");
        free(sckt);
		return 0;
	}

    bcopy((char *) sckt->socket_host->h_name, (char *) &sckt->socket_info.sin_addr, sckt->socket_host->h_length);    // copy host IP to socket adress

    //--

    sckt->socket_identifier = socket(AF_INET, socket_type, 0);
    if (sckt->socket_identifier < 0) {
        fprintf(stderr, "ERRO, ao tentar abrir o socket\n");
        free(sckt);
		return NULL;
	}

    //--

    return sckt;
}


// Create and opens a listener-socket.
// socket_type: is either SOCK_STREAM for TCP | SOCK_DGRAM for UDP
// port: the number of the port this socket opens
// maxConnections: TCP only, set how many connections the server will allow
socket_listener_info* con_create_listener_socket(int socket_type, int port, int maxConnections) {

    //// ==== Alloc memory for the socket

    socket_listener_info* sckt = malloc(sizeof(socket_listener_info));
    if (sckt == NULL) {
        fprintf(stderr, "ERRO, ao criar socket\n");
        return NULL;
    }

    //// ==== Set basic variables

    sckt->socket_info.sin_port = htons(port);
    sckt->socket_info.sin_family = AF_INET;     // Always AF_INET == IPv4 Adress use

    //// ==== Set server-IP via this machine's name

    if ((sckt->socket_host = gethostbyname(netInfo.host_name)) == NULL){
		fprintf(stderr, "ERRO, host que deveria ser essa maquina nao encontrado\n");
        free(sckt);
		return 0;
	}

    bcopy((char *) sckt->socket_host->h_name, (char *) &sckt->socket_info.sin_addr, sckt->socket_host->h_length);    // copy host IP to socket adress

    //// ==== Obtain socket listener identifier

    sckt->socket_identifier = socket(AF_INET, socket_type, 0);
    if (sckt->socket_identifier < 0) {
        fprintf(stderr, "ERRO, ao tentar abrir o socket\n");
        free(sckt);
		return NULL;
	}

    //// ==== Set list of senders identifiers for the server

    sckt->tcp_listeners_size = maxConnections;
    sckt->tcp_listeners = malloc(sizeof(int) * sckt->tcp_listeners_size);
    if ((sckt->tcp_listeners == NULL) && (sckt->tcp_listeners_size > 0)) {
        fprintf(stderr, "ERRO, ao criar lista de conexoes do server\n");
        free(sckt);
        return 0;
    }

    //// ==== Bind the hearing channel for the server to use

    if (bind(sckt->socket_identifier, (struct sockaddr *) &sckt->socket_info, sizeof(sckt->socket_info)) < 0){
		fprintf(stderr, "ERRO: falha ao estabelecer canal de escuta\n");
        free(sckt->tcp_listeners);
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

    for(int i = 0; i < sckt->tcp_listeners_size; i++) {
        close(sckt->tcp_listeners[i]);
    }

    free(sckt->tcp_listeners);

    //--

    free(sckt);
}



//--------------------------------------