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



    // Run UDP test



    // Run TCP test, no window



    // Run TCP test, window



    // Finish workspace

    return 0;
}