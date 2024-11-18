

typedef struct __netInfo {
    char* host;
    char* dados;
    int numBytesReceiving;

    char buffer[BUFSIZ];

    int sock_descriptor;
    struct sockaddr_in sa;
    struct hostent *hp;
} connection_info;