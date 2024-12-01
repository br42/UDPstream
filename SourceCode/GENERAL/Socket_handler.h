

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
socket_listener_info* socket_create_listener(int socket_type);

// necessary functions to properly close a sender-socket
void socket_close_sender(socket_sender_info* sckt);

// necessary functions to properly close a listener-socket
void socket_close_listener(socket_listener_info* sckt);

// fill a buffer up to the size determined
void socket_fill_buffer(socket_sender_info* sckt, unsigned long sizeToFill);

// compare the given sequence number with the current sequence
// saves the difference as package lost
void socket_compare_sequence(int sequence_numb);

// allows the sequence to be changed globally
int socket_set_sequence(int newSeq);
// returns the amount of package lost
int socket_get_package_lost();