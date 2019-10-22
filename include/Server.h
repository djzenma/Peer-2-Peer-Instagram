#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include "RequestReply.h"

using namespace std;

class Server {
private:
    char buffer [1024];

public:
    Server(const char *destinationPort, const char *destinationIp);
};
#endif 