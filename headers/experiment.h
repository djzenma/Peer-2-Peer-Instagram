#ifndef _EXPERIMENT_H_
#define _EXPERIMENT_H_
#include "Client.h"
#include "Server.h"


void varyLoad(Client * c, int num_reqs);
void varyBuffSize(Server *s, int buff_size);

#endif