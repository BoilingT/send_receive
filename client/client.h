#ifndef _client_h_
#define _client_h_

#include "../global.h"

typedef struct s_connection_t *server_t;
typedef struct s_connection_t *client_t;

void client_destroy(client_t server);
int  client_start(client_t server);
int  client_stop(client_t server);
int  client_status(client_t server);

void client_send(client_t client, char *buffer, size_t size);
void client_recieve(client_t client, char *out_buffer, size_t size);

#endif