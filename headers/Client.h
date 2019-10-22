#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <string.h>
#include "RequestReply.h"


class Client {
private:
    char buffer [1024];

public:
    Client(const char *destinationPort, const char *destinationIp);
};
#endif