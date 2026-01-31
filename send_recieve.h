#ifndef _send_recieve_h_
#define _send_recieve_h_

#include <pthread.h>

#include "connection.h"
#include "ui.h"

#define MAX_CLIENTS 10

// Port that will be used when connecting the socket
#define PORT_NR 8123

/*
    When the client has connected it will send "Hello World"
    to the server and the server will print this to the console.
*/
void init();

#endif