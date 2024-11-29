

#define MAXHOSTNAME 64

typedef struct __netInfo {
    char host_name[MAXHOSTNAME];        // stores this machine's host name
} network_info;



//--------------------------------------



typedef struct __sktSndInfo {
    struct hostent* socket_host;        // net host responsible for this socket

    struct sockaddr_in socket_info;     // basic information of this socket
    int socket_identifier;              // numerical identifier of the open socket

    char buffer[BUFSIZ];                // data that will be transmited by this socket
} socket_sender_info;



//--------------------------------------



#define MAXFILA 5

typedef struct __sktLstInfo {
    struct hostent* socket_host;                // net host responsible for this socket

    struct sockaddr_in socket_info;             // basic information of this socket
    int socket_identifier;                      // numerical identifier of the open socket

    struct sockaddr_in listener_socket_info;    // basic information of the receiver socket

    char buffer[BUFSIZ];                        // data that is received by this socket
} socket_listener_info;



//--------------------------------------