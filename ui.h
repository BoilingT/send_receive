#ifndef _ui_h_
#define _ui_h_

#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER 255

#define OPTIONS 6

enum request_t
{
    MENU,
    START_SERVER,
    STOP_SERVER,
    ADD_CLIENT,
    DEL_CLIENT,
    STOP
};

int  read_int();
void print_options();

#endif