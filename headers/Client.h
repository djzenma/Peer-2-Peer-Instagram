#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <string.h>
#include "RequestReply.h"
#include "utils.h"
#include "Message.h"

class Client {
private:
    char buffer [2048];
    RequestReply* reqReply;

public:
    Client(const char* hostname, const char* port);

    int execute(char * msg);
    void executePrompt();
    ~Client();
};
#endif