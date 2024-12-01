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

    fprintf(stderr, "       Servidor(1) ou Cliente(2) ou send FIM separado(3)\n");
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

            //// ==== start sending messages

            int bytesSent;
            
            float timeStart = clock();
            for (bytesSent = 0; bytesSent < SENDSIZE; bytesSent += MESSAGESIZE) {
                if (uclt_send_message(scktS, MESSAGESIZE) < 0) {
                    bytesSent -= MESSAGESIZE;
                    fprintf(stderr, "ERRO: ao enviar mensagem\n");
                    break;
                }
            }
            float timeEnd = clock();

            uclt_send_FIM_message(scktS);
            
            //// ==== close socket and print output

            fprintf(stderr, "       Bytes enviador : %d\n", bytesSent);
            fprintf(stderr, "       Tempo total : %f\n", ((timeEnd - timeStart) / CLOCKS_PER_SEC));

            socket_close_sender(scktS);

        break;

        case (3) :  // FIM de emergencia

            //// ==== get Server name

            fprintf(stderr, "       Insira o IP do Host do servidor\n\n");
            scanf("%s", ipDestino);

            //// ==== Create variables and sockets
            
            socket_sender_info* scktSS = socket_create_sender(ipDestino, SOCK_DGRAM);
            uclt_prep_sender_socket(scktSS);

            //// ==== start sending messages

            uclt_send_FIM_message(scktSS);
            
            //// ==== close socket and print output

            socket_close_sender(scktSS);

        break;
    }

    //--

    

    

    // Run UDP test



    // Run TCP test, no window



    // Run TCP test, window



    // Finish workspace

    return 0;
}