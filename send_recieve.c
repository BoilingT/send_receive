#include "send_recieve.h"

/*
    Private
*/

struct s_shared
{
    server_t        server;
    pthread_mutex_t mutex;
    pthread_t       server_pid;
    pthread_t      *client_pids;
    int             client_count;
} s_shared;

struct s_args
{
    server_t server;
    client_t client;
};

void *_server_thread(void *args)
{
    int proceed = 0;
    while (!proceed)
    {
        pthread_mutex_lock(&s_shared.mutex);
        proceed = 1;
        pthread_mutex_unlock(&s_shared.mutex);
    }
    log_debug("Server Thread Start");
    client_t client = (client_t)calloc(1, sizeof(client));
    while (connection_accept((server_t)args, client))
    {
        log_info("Connection Successful!");
    }
    free(client);
    log_debug("Server Thread End");

    return NULL;
}

int _start_server(server_t server)
{
    if (server_status(server) == LISTENING)
    {
        printf("Server is already active\n");
        return 1;
    }

    server_start(server);

    pthread_create(&s_shared.server_pid, NULL, _server_thread, server);
    return 1;
}

int _stop_server(server_t server)
{
    if (!server)
    {
        log_error("Could not stop server because server is null");
        return 0;
    }

    server_stop(server);
    pthread_join(s_shared.server_pid, NULL);
    return 1;
}

void *_client_thread(void *args)
{
    log_debug("Client Thread Start");

    connection_connect((client_t)args, s_shared.server);
    log_debug("Client Thread End");

    return NULL;
}

void _add_client(client_t *clients)
{
    if (s_shared.client_count >= MAX_CLIENTS) return;
    clients[s_shared.client_count] = connection_init(PORT_NR);

    // client_start()

    pthread_create(&s_shared.client_pids[s_shared.client_count], NULL, _client_thread, clients[s_shared.client_count]);

    s_shared.client_count++;
}

void _del_client(client_t *clients)
{
    if (s_shared.client_count <= 0) return;
    connection_destroy(clients[s_shared.client_count - 1]);
    pthread_join(s_shared.client_pids[s_shared.client_count - 1], NULL);

    s_shared.client_count--;
}

int _stop(server_t server, client_t *clients)
{
    _stop_server(server);

    // Delete and stop all clients
    for (int i = 0; i < s_shared.client_count; i++)
    {
        _del_client(clients);
    }
}

void _print_status(server_t server, client_t *clients)
{
    pthread_mutex_lock(&s_shared.mutex);

    char *state_buffer = "Offline (Null)";

    if (server)
    {
        switch (server_status(server))
        {
        case OFFLINE   : state_buffer = "Offline"; break;
        case READY     : state_buffer = "Ready"; break;
        case LISTENING : state_buffer = "Listening"; break;
        default        : break;
        }
    }

    printf("-------------------------\n");
    printf("Server (fd: %d): %s\n", connection_fd(server), state_buffer);
    for (int i = 0; i < s_shared.client_count; i++)
    {
        printf("Client (%d) fd: %d\n", i + 1, connection_fd(clients[i]));
    }

    printf("-------------------------\n");
    pthread_mutex_unlock(&s_shared.mutex);
}

int _process_request(enum request_t request, server_t server, client_t *clients)
{
    switch (request)
    {
    case MENU         : _print_options(); break;
    case START_SERVER : _start_server(server); break;
    case STOP_SERVER  : _stop_server(server); break;
    case ADD_CLIENT   : _add_client(clients); break;
    case DEL_CLIENT   : _del_client(clients); break;
    case STOP         : _stop(server, clients); return 0;
    default           : return 0;
    }

    return 1;
}

/*
    Public
*/

void init()
{
    server_t server = connection_init(PORT_NR);

    connection_bind(server);

    s_shared.server = server;
    // Create list of clients
    client_t clients[MAX_CLIENTS];
    s_shared.client_count = 0;

    s_shared.client_pids = malloc(sizeof(int) * MAX_CLIENTS);
    s_shared.server_pid  = 0;

    pthread_mutex_init(&s_shared.mutex, NULL);

    enum request_t request = STOP;

    _print_options();

    do
    {
        // pthread_mutex_lock(&s_shared.mutex);
        _print_status(server, clients);
        printf("\nOperation <nr>: ");
        // pthread_mutex_unlock(&s_shared.mutex);
        request = read_int() - 1;
        printf("\n");

    } while (_process_request(request, server, clients));

    pthread_mutex_unlock(&s_shared.mutex);

    _stop(server, clients);

    connection_destroy(server);

    free(s_shared.client_pids);
    pthread_mutex_destroy(&s_shared.mutex);

    printf("Exited\n");
}