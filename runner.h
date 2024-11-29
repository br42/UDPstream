#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include <errno.h>



#include "SourceCode/GENERAL/Structures.h"

#include "SourceCode/GENERAL/Socket_handler.h"

#include "SourceCode/UDP/UDP_server.h"
#include "SourceCode/UDP/UDP_cliente.h"

#include "SourceCode/TCP/TCP_server.h"
#include "SourceCode/TCP/TCP_cliente.h"