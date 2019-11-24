#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include "RequestReply.h"
#include <string>
#include <cstring>
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
        void updateCount(int image_id, int num_views);

    public:
        Server(const char * listen_hostname,const char * listen_port);
        int serveRequest();
        ~Server();
};
#endif
