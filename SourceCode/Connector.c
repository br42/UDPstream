#include "../runner.h"



//--------------------------------------

connection_info netInfo;

//--------------------------------------



void net_connect(char* host) {
    netInfo.hp = gethostbyname(host);
    if (netInfo.hp == NULL) {
		// erro ao achar host
        fprintf(stderr, "ERRO, ao encontrar host\n");
		return 1;
	}

    //--

    
}