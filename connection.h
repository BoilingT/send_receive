#ifndef _connection_h_
#define _connection_h_

#include "global.h"

typedef enum connection_state_t connection_state_t;
typedef s_connection_t         *connection_t;

connection_t connection_init(short port_nr);
int          connection_stop(connection_t connection);
int          connection_destroy(connection_t connection);

/*
    Create a socket using INET protocol family,
    using type STREAM and TCP protocol.
*/
int connection_bind(connection_t server);
int connection_listen(connection_t server, int connection_requests);
int connection_accept(connection_t server, connection_t client);
int connection_connect(connection_t host, connection_t peer);

int connection_fd(connection_t connection);

int is_offline(connection_t connection);
int is_ready(connection_t connection);
int is_listening(connection_t connection);
#endif