#include "connection.h"
#include "connection_internal.h"

connection_t connection_init(short port_nr)
{
    connection_t connection = (connection_t)calloc(1, sizeof(*connection));

    if (!connection)
    {
        log_error("Server: Could not be allocated");
        return NULL;
    }

    connection->state = OFFLINE;

    connection->fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    log_info("Server: Socket (%d) has been created", connection->fd);

    if (connection->fd == -1)
    {
        log_error("Server: Could not create tcp socket");
        perror("Reason");
        free(connection);
        return NULL;
    }

    connection->addr_in.sin_family      = PF_INET;
    connection->addr_in.sin_addr.s_addr = INADDR_ANY;
    connection->addr_in.sin_port        = htons(port_nr);

    log_info("Server: Server has been initialized");

    return connection;
}

int connection_stop(connection_t connection)
{
    if (!is_listening(connection)) return 0;

    if (shutdown(connection->fd, SHUT_RDWR) == -1)
    {
        log_error("Server: Could not shutdown");
        perror("Reason");
        return 0;
    }
    else
    {
        log_info("Server: (%d) Has been shutdown", connection->fd);
    }

    memset(&connection->addr_in, 0, sizeof(connection->addr_in));

    connection->state = READY;

    return 1;
}

// Stops and closes the connection
int connection_destroy(connection_t connection)
{
    if (!connection) return 0;

    if (!is_offline(connection))
    {
        connection_stop(connection);
    }

    close(connection->fd);

    connection->state = OFFLINE;

    log_info("Socket (%d) has been closed", connection->fd);

    free(connection);

    log_info("Server has been destroyed");

    return 1;
}

int connection_bind(connection_t connection)
{
    if (!is_offline(connection))
    {
        log_info("Connection is already active");
        return 0;
    }

    int result = bind(connection->fd, (struct sockaddr *)&connection->addr_in, sizeof(connection->addr_in));
    if (result < 0)
    {
        log_error("Socket could not be bound, fd: %d", connection->fd);
        perror("Reason");
        return 0;
    }

    log_info("Socket has been bound");

    connection->state = READY;

    return 1;
}

int connection_listen(connection_t connection, int connection_requests)
{
    int result = listen(connection->fd, connection_requests);
    if (result == -1)
    {
        log_warn("Could not accept connection");
        perror("Reason");
        return 0;
    }

    log_info("Socket is listening");

    connection->state = LISTENING;

    return 1;
}

// int *out_fd, struct sockaddr_in *client_addr, socklen_t *client_addr_len
int connection_accept(connection_t host, connection_t client)
{
    if (!host) return 0;

    client->fd = accept(host->fd, (struct sockaddr *)&client->addr_in, &client->addr_length);

    log_info("Awaiting connection");
    if (client->fd == -1)
    {
        log_warn("Could not accept connection");
        perror("Reason");
        return 0;
    }

    printf("Connection accepted (%d)", client->fd);
    return 1;
}

int connection_connect(connection_t host, connection_t peer)
{
    if (connect(host->fd, (struct sockaddr *)&peer->addr_in, sizeof(peer->addr_in)) == -1)
    {
        log_warn("Could not connect to socket");
        perror("Reason");
    }
}

connection_state_t connection_status(connection_t connection)
{
    if (!connection) return OFFLINE;
    return connection->state;
}

int connection_fd(connection_t connection)
{
    return connection->fd;
}

int is_offline(connection_t connection)
{
    if (!connection) return 1;
    return connection->state == OFFLINE;
}

int is_ready(connection_t connection)
{
    if (!connection) return 0;
    return connection->state == READY;
}

int is_listening(connection_t connection)
{
    if (!connection) return 0;
    return connection->state == LISTENING;
}