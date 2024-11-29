#include "../../runner.h"



//--------------------------------------



// prepares socket to be a UDP listener
// returns 1 for sucess and 0 for error
int usvr_prep_listener_socket(socket_listener_info* sckt) {

    // UDP does not need any preparation to receive messages
    return 1;
}



//--------------------------------------



// receive a message from the internet
int usvr_receive_message() {

}