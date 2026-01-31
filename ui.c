#include "ui.h"

int read_int()
{
    char buffer[MAX_BUFFER];
    fgets(buffer, sizeof(buffer), stdin);
    return atoi(buffer);
}

/*
    Server: Online/Offline
    Clients: 0+

    1. Start Server
    2. Stop Server
    3. Start Client
    4. Stop Client <nr>
    5. Shutdown
*/
void print_options()
{
    for (int i = 0; i < OPTIONS; i++)
    {
        char *buffer;
        switch (i)
        {
        case MENU         : buffer = "Print Menu"; break;
        case START_SERVER : buffer = "Start Server"; break;
        case STOP_SERVER  : buffer = "Stop Server"; break;
        case ADD_CLIENT   : buffer = "Add Client"; break;
        case DEL_CLIENT   : buffer = "Del Client"; break;
        case STOP         : buffer = "Stop"; break;
        }

        printf("%d. %s\n", (i + 1), buffer);
    }
}