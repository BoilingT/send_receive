#include "server.h"
#include "../connection_internal.h"

/*
    Private
*/

int _is_error(int result)
{
    return result == -1;
}

/*
    Public
*/

// Listen
int server_start(server_t server)
{
    if (!server) return 0;

    if (!connection_listen(server, CONNECTION_REQUESTS))
    {
        log_error("Could not open for connections");
        return 0;
    }

    log_info("Server Started");

    return 1;
}

int server_stop(server_t server)
{
    if (!server)
    {
        log_warn("Server: Could not be deallocated");
        return 0;
    }

    connection_stop(server);

    return 0;
}

int server_status(server_t server)
{
    if (!server) return OFFLINE;

    return server->state;
}