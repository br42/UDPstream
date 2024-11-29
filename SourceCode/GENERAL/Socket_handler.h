

// required initial preparation to use the network
void sck_network_prep();


// Create and opens a sender-socket.
// socket_type: is either SOCK_STREAM for TCP | SOCK_DGRAM for UDP
// host: the server name to send messages to
// port: the number of the port this socket opens
socket_sender_info* socket_create_sender(char* host, int socket_type);


// Create and opens a listener-socket.
// socket_type: is either SOCK_STREAM for TCP | SOCK_DGRAM for UDP
// port: the number of the port this socket opens
// maxConnections: TCP only, set how many connections the server will allow
socket_listener_info* socket_create_listener(int socket_type, int maxConnections);

// necessary functions to properly close a sender-socket
void socket_close_sender(socket_sender_info* sckt);

// necessary functions to properly close a listener-socket
void socket_close_listener(socket_listener_info* sckt);

// fill a buffer up to the size determined
void socket_fill_buffer(socket_sender_info* sckt, int sizeToFill);