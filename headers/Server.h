#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include "RequestReply.h"
#include "utils.h"
#include <string>
#include <cstring>
#include "Message.h"
#include "Database.h"

using namespace std;


class Server {

    private:
        int reqNum , picNum = -1;
        const char * port;
        const char * hostname;
        RequestReply * reqReply;
        string myName ;
        Database * db;

        void dispatch(Message & m);
        
    public:
        Server(const char * listen_hostname,const char * listen_port);
        void dec_count(Message m);
        int serveRequest();
        ~Server();
};
#endif 