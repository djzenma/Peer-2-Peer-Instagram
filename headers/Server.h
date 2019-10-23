#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include "RequestReply.h"
#include "utils.h"

using namespace std;

class Server {

    private:
        char * buffer;
        int buff_size = 1024;
        RequestReply * reqReply;

    public:
        Server(const char * listen_hostname,const char * listen_port);
        void setBufferSize(int size);
        void serveRequest();
        ~Server();
};
#endif 