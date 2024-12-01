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

    //// ================================================ Prepare workspace

    int runnerType;
    char ipDestino[64];

    fprintf(stderr, "       Servidor(1) ou Cliente(2) ou enviar mensagem FIM(5)\n");
    fprintf(stderr, "       Servidor(3) ou Cliente(4) TCP\n");
    scanf("%d", &runnerType);

    //// ================================================ PERFORM ACTION REQUESTED

    int bytesReceived;
    int bytesSent;

    float timeStart;
    float timeEnd;

    switch(runnerType) {

        //// ================================================ EXIT

        default:
            fprintf(stderr, "Saindo sem fazer nada...\n");
            return 0;
        break;

        //// ================================================ SERVIDOR TCP

        case (1):

            //// ==== Create variables and sockets

            socket_listener_info* scktL = socket_create_listener(SOCK_DGRAM);
            usvr_prep_listener_socket(scktL);

            //// ==== receive all messages until FIM is received
            
            bytesReceived = 0;

            while(usvr_receive_message(scktL) >= 0) {
                bytesReceived += MESSAGESIZE;
            }

            //// ==== print output and close socket

            fprintf(stderr, "       Perda de pacotes: %d\n", socket_get_package_lost());
            fprintf(stderr, "       bytes recebidos: %d\n", bytesReceived);

            socket_close_listener(scktL);

        break;

        //// ================================================ CLIENTE UDP

        case (2):

            //// ==== get Server name

            fprintf(stderr, "       Insira o IP do Host do servidor\n\n");
            scanf("%s", ipDestino);

            //// ==== Create variables and sockets
            
            socket_sender_info* scktS = socket_create_sender(ipDestino, SOCK_DGRAM);
            uclt_prep_sender_socket(scktS);

            //// ==== start sending messages
            
            timeStart = clock();
            for (bytesSent = 0; bytesSent < SENDSIZE; bytesSent += MESSAGESIZE) {
                if (uclt_send_message(scktS, MESSAGESIZE) < 0) {
                    bytesSent -= MESSAGESIZE;
                    fprintf(stderr, "ERRO: ao enviar mensagem\n");
                    break;
                }
            }
            timeEnd = clock();

            uclt_send_FIM_message(scktS);
            
            //// ==== close socket and print output

            fprintf(stderr, "       Bytes enviados : %d\n", bytesSent);
            fprintf(stderr, "       Tempo total : %f\n", ((timeEnd - timeStart) / CLOCKS_PER_SEC));

            socket_close_sender(scktS);

        break;

        //// ================================================ FIM DE EMERGENCIA UDP

        case (5) :

            //// ==== get Server name

            fprintf(stderr, "       Insira o IP do Host do servidor\n\n");
            scanf("%s", ipDestino);

            //// ==== Create variables and sockets
            
            socket_sender_info* scktSE = socket_create_sender(ipDestino, SOCK_DGRAM);
            uclt_prep_sender_socket(scktSE);

            //// ==== start sending messages

            uclt_send_FIM_message(scktSE);
            
            //// ==== close socket and print output

            socket_close_sender(scktSE);

        break;

        //// ================================================ SERVIDOR TCP

        case (3):

            //// ==== create socket

            socket_listener_info* scktLT = socket_create_listener(SOCK_STREAM);
            tsvr_prep_listener_socket(scktLT);

            //// ==== accept connection

            if (tsvr_accept_listener(scktLT) == 0) {
                fprintf(stderr, "ERRO: ao aceitar um socket");
                exit(0);
            }

            //// ==== receive messages

            bytesReceived = 0;
            int msgSize;
            
            while ((msgSize = tsvr_receive_message(scktLT)) > 0 && bytesReceived < SENDSIZE) {
                bytesReceived += msgSize;
            }

            //// ==== stops listening

            tsvr_stop_listening(scktLT);

            //// ==== print output and close socket

            fprintf(stderr, "       bytes recebidos : %d\n", bytesReceived);

            socket_close_listener(scktLT);

        break;

        //// ================================================ CLIENTE TCP

        case (4):   // Cliente TCP

            //// ==== get Server name
            
            fprintf(stderr, "       Insira o IP do Host do servidor\n\n");
            scanf("%s", ipDestino);

            //// ==== create socket
            
            socket_sender_info* scktST = socket_create_sender(ipDestino, SOCK_STREAM);
            tclt_prep_sender_socket(scktST);

            //// ==== send messages

            timeStart = clock();
            for (bytesSent = 0; bytesSent < SENDSIZE; bytesSent += MESSAGESIZE) {
                tclt_send_message(scktST, MESSAGESIZE);
            }
            timeEnd = clock();

            //// ==== print output and close socket

            fprintf(stderr, "       Bytes enviados : %d\n", bytesSent);
            fprintf(stderr, "       Tempo total : %f\n", ((timeEnd - timeStart) / CLOCKS_PER_SEC));

            socket_close_sender(scktST);

        break;
    }

    return 0;
}