#include "../runner.h"



//--------------------------------------



// prepares socket to be a UDP listener
// returns 1 for sucess and 0 for error
int udp_prepare_listener_socket(socket_listener_info* sckt) {

    // UDP does not need any preparation to receive messages
    return 1;
}


// prepares socket to be a UDP sender
// returns 1 for sucess and 0 for error
int udp_prepare_sender_socket(socket_sender_info* sckt) {

    // UDP does not need any preparation for the sender machine
    return 1;
}