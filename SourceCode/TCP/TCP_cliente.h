// prepares socket to be a TCP sender
// returns 1 for sucess and 0 for error
int tclt_prep_sender_socket(socket_sender_info* sckt);

// Send 1 message to server
// return the time it took to send or negative for error
float tclt_send_message(socket_sender_info* sckt, int msgSize);