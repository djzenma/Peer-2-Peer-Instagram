#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include "RequestReply.h"
#include "utils.h"
#include <string>
#include <cstring>
#include "Message.h"

using namespace std;


enum serviceOperations{
    SendImage = 0,
    GrantAccess = 1,
    DecrementView = 2,
    SendSample = 3,
    SendImages = 4
};

class Server {

    private:
        int reqNum , picNum = -1;
        const char * port;
        const char * hostname;
        RequestReply * reqReply;
        string myName ;
        void dispatch(Message & m);
        
    public:
        Server(const char * listen_hostname,const char * listen_port);
        void thread_server(bool parent);
        int serveRequest(std::string serverName);
        ~Server();
};
#endif 
