// prepares socket to be a TCP sender
// returns 1 for sucess and 0 for error
int tclt_prep_sender_socket(socket_sender_info* sckt);

// Send 1 message to server
// return 1 for sucess, 0 for error
int tclt_send_message(socket_listener_info* sckt, int msgSize);