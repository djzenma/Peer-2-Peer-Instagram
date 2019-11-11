#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include "RequestReply.h"
#include "utils.h"
#include <string>
#include <cstring>

using namespace std;

class Server {

    private:
    char buffer [2048];
    int reqNum , picNum = -1;
    const char * port;
    const char * hostname;
    RequestReply * reqReply;
    string name ;
    public:
        Server(const char * listen_hostname,const char * listen_port);
        void setBufferSize(int size);
        void serveRequest();
        ~Server();
};
#endif 