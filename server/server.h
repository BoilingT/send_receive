#ifndef _server_h_
#define _server_h_

#include "../global.h"
#include "../connection.h"

// Amount of requests that will be tried
#define CONNECTION_REQUESTS 1

typedef struct s_connection_t *server_t;
typedef struct s_connection_t *client_t;

int server_start(server_t server);
int server_stop(server_t server);
int server_status(server_t server);

#endif