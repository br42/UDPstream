

#define MAXHOSTNAME 64

typedef struct __netInfo {
    char host_name[MAXHOSTNAME];        // stores this machine's host name
} network_info;



//--------------------------------------



typedef struct __sktSndInfo {
    struct hostent* socket_host;        // net host responsible for this socket

    struct sockaddr_in socket_info;     // basic information of this socket
    int socket_identifier;              // numerical identifier of the open socket

    char buffer[BUFSIZ];                // data that is transmited and received by socket
} socket_sender_info;


typedef struct __sktLstInfo {
    struct hostent* socket_host;        // net host responsible for this socket

    struct sockaddr_in socket_info;     // basic information of this socket
    int socket_identifier;              // numerical identifier of the open socket

    struct sockaddr_in receiver_info;   // basic information of the receiver socket
    int* tcp_listeners;                 // TCP exclusive, list of server-cliente connection identifiers
    int tcp_listeners_size;             // the amount of connections allowed in the tcp server

    char buffer[BUFSIZ];                // data that is transmited and received by socket
} socket_listener_info;