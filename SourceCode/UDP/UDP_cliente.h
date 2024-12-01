// prepares socket to be a UDP sender
// returns 1 for sucess and 0 for error
int uclt_prep_sender_socket(socket_sender_info* sckt);

// sends 1-1-1 to the server stating as the last message
// will wait for a response and resend if needed
float uclt_send_FIM_message(socket_sender_info* sckt);

// fill buffer and send 1 message to server
// msgSize is the amount in bytes of data to transfer
// return the time it took to send or negative for error
int uclt_send_message(socket_sender_info* sckt, int msgSize);