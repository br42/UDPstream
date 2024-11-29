#include "../../runner.h"



//--------------------------------------



// prepares socket to be a TCP sender
// returns 1 for sucess and 0 for error
int tclt_prep_sender_socket(socket_sender_info* sckt) {

    if(connect(sckt->socket_identifier, (struct sockaddr *) &sckt->socket_info, sizeof(sckt->socket_info)) < 0) {
      puts("ERRO: falha ao connectar a algum servidor\n");
      return 0;
    }

    //--

    return 1;
}



//--------------------------------------



// allow socket-listener to accept a single connection
// return 1 for sucess, 0 for error
int tclt_send_message(socket_listener_info* sckt) {
    

    //--

    

    //--

    return 1;
}



//--------------------------------------