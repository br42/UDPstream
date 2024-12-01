

#define PORT 6287               // the port we'll be using
#define SENDSIZE 1000           // amount of bytes to send
#define MESSAGESIZE 1           // the amount of bytes per message
#define LOOPBACK "localhost"    // Nome da maquina de loopback

#define MAXHOSTNAME 64

typedef struct __netInfo {
    char host_name[MAXHOSTNAME];        // stores this machine's host name

    unsigned char seqNumber;                     // number of this message's sequence [0, 255]

    int lost_package;
} network_info;



//--------------------------------------



typedef struct __sktSndInfo {
    struct sockaddr_in socket_info;     // basic information of this socket
    int socket_identifier;              // numerical identifier of the open socket

    unsigned char buffer[BUFSIZ];                // data that will be transmited by this socket
} socket_sender_info;



//--------------------------------------



#define MAXFILA 5

typedef struct __sktLstInfo {
    struct sockaddr_in socket_info;             // basic information of this socket
    int socket_identifier;                      // numerical identifier of the open socket

    struct sockaddr_in listener_socket_info;    // basic information of the receiver socket
    int listener_identifier;                    // numerical identifier of the listener socket

    unsigned char buffer[BUFSIZ];               // data that is received by this socket
} socket_listener_info;



//--------------------------------------