// prepares socket to be a TCP listener
// returns 1 for sucess and 0 for error
int tsvr_prep_listener_socket(socket_listener_info* sckt);

// Accept a connection request
// read messages until stop receiving them
// close connection
// return 1 for sucess, 0 for error
int tsvr_receive_message(socket_listener_info* sckt);