// prepares socket to be a UDP sender
// returns 1 for sucess and 0 for error
int uclt_prep_sender_socket(socket_sender_info* sckt);

// fill buffer and send message to server
// return the time it took to send or nengative for error
float uclt_send_message(socket_sender_info* sckt, int msgSize);