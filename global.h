#ifndef _global_h_
#define _global_h_

#include <netinet/in.h> // Types
#include <sys/socket.h> // Socket Procedures
#include <netdb.h>      // Network Procedures

#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logger/log_manager.h" // Logging
#include <errno.h>              // Error messages

typedef enum connection_state_t
{
    OFFLINE,
    READY,
    LISTENING
} connection_state_t;

// Opaque pointer
typedef struct s_connection_t s_connection_t;

#endif