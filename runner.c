// Luiz Fernando, Bruno Dal Pontte

#include "runner.h"


/*
    This is the main file that runs our tests.

    Our tests include
        UDP testing of 1 mB transference
        TCP testing of 1 mB transference
    
    These will be tested using
        Shortest possible messages.
        Longest possible messages.
        Window behaviour (For TCP)                  *IGNORE*
        no Window behaviour (For TCP)

    We will monitor the following results
        Package lost (re-sent message)
        Overall transference time
        Network path consistency (in porcentage)    *IGNORE*
*/


// main code that runs our tests
int main(int argc, char* argv[]) {

    sck_network_prep();

    // Prepare workspace

    int runnerType;
    char ipDestino[64];

    fprintf(stderr, "       Servidor(1) ou Cliente(2) ou enviar mensagem FIM(5)\n");
    fprintf(stderr, "       Servidor(3) ou Cliente(4) TCP\n");
    scanf("%d", &runnerType);


    switch(runnerType) {
        default:    // exit
            fprintf(stderr, "Saindo sem fazer nada...\n");
            return 0;
        break;


        case (1):   // servidor

            //// ==== Create variables and sockets

            socket_listener_info* scktL = socket_create_listener(SOCK_DGRAM);
            usvr_prep_listener_socket(scktL);

            //// ==== receive all messages until FIM is received
            
            int bytesReceived = 0;

            while(usvr_receive_message(scktL) >= 0) {
                bytesReceived += MESSAGESIZE;
            }

            //// ==== print output and close socket

            fprintf(stderr, "       Perda de pacotes: %d\n", socket_get_package_lost());
            fprintf(stderr, "       bytes recebidos: %d\n", bytesReceived);

            socket_close_listener(scktL);

        break;


        case (2):   // Cliente

            //// ==== get Server name

            fprintf(stderr, "       Insira o IP do Host do servidor\n\n");
            scanf("%s", ipDestino);

            //// ==== Create variables and sockets
            
            socket_sender_info* scktS = socket_create_sender(ipDestino, SOCK_DGRAM);
            uclt_prep_sender_socket(scktS);
            uclt_send_message(scktS, 3);
            
            fprintf(stderr, "Terminado...\n");

        break;

        case (3):   // Servidor TCP

            socket_listener_info* scktLT = socket_create_listener(SOCK_STREAM);

            tsvr_prep_listener_socket(scktLT);
            tsvr_receive_message(scktLT);

            fprintf(stderr, "%d - %d - %d\n", scktLT->buffer[0], scktLT->buffer[1], scktLT->buffer[2]);

        break;

        case (4):   // Cliente TCP
            fprintf(stderr, "       Insira o IP do Host do servidor\n\n");
            scanf("%s", ipDestino);

            //--
            
            socket_sender_info* scktST = socket_create_sender(ipDestino, SOCK_STREAM);

            tclt_prep_sender_socket(scktST);
            tclt_send_message(scktST, 3);
            
            fprintf(stderr, "Terminado...\n");

        break;
    }

    //--

    

    

    // Run UDP test



    // Run TCP test, no window



    // Run TCP test, window



    // Finish workspace

    return 0;
}