// prepares socket to be a TCP listener
// returns 1 for sucess and 0 for error
int tsvr_prep_listener_socket(socket_listener_info* sckt);

// Accept a connection request
// return 1 for success, 0 for error
int tsvr_accept_listener(socket_listener_info* sckt);

// close listener connection
// return 1 for success, 0 for error
int tsvr_stop_listening(socket_listener_info* sckt);

// read 1 message from listener socket
// return the size of the message
int tsvr_receive_message(socket_listener_info* sckt);