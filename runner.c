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
        Window behaviour (For TCP)
        no Window behaviour (For TCP)

    We will monitor the following results
        Package lost (re-sent message)
        Overall transference time
        Network path consistency (in porcentage)
*/


// main code that runs our tests
int main(int argc, char* argv[]) {

    sck_network_prep();

    // Prepare workspace

    int runnerType;
    int ipDestino;

    fprintf(stderr, "       Servidor(1) ou Cliente(2)\n");
    scanf("%d", &runnerType);


    switch(runnerType) {
        default:    // exit
            fprintf(stderr, "Saindo sem fazer nada...\n");
            return 0;
        break;

        case (1):   // servidor

            socket_listener_info* sckt = socket_create_listener(SOCK_DGRAM);

        break;

        case (2):   // Cliente
            fprintf(stderr, "       Insira o IP do Host do servidor\n\n");
            scanf("%d", &ipDestino);

            //--



        break;
    }

    //--

    

    

    // Run UDP test



    // Run TCP test, no window



    // Run TCP test, window



    // Finish workspace

    return 0;
}