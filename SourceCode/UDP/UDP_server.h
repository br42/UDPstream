// prepares socket to be a UDP listener
// returns 1 for sucess and 0 for error
int usvr_prep_listener_socket(socket_listener_info* sckt);

// receive a message from the internet
int usvr_receive_message(socket_listener_info* sckt);