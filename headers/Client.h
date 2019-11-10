#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <string.h>
#include "RequestReply.h"
#include "utils.h"
#include "Message.h"

class Client {
private:
    char * buffer;
    int buff_size = 1024;
    RequestReply* reqReply;
    const char * port;
    const char * hostname;
    int req ;

public:
    Client(const char* hostname, const char* port);

    int execute(char * msg);
    int requestSamples();
    int requestNumber (int req);
    void executePrompt();
    ~Client();
};
#endif