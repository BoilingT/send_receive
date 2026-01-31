#ifndef _connection_internal_h_
#define _connection_internal_h_

#include "global.h"

typedef struct s_connection_t
{
    int                fd;          // File Descriptor
    struct sockaddr_in addr_in;     // Address
    socklen_t          addr_length; // Address Length
    connection_state_t state;
} s_connection_t;

#endif