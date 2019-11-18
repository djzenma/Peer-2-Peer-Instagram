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
<<<<<<< HEAD
        string myName ;
=======
        string name ;
        Database * db;
>>>>>>> 0e5ecd2388631a12ef5cc0c5ce0d97407971cd95

        void dispatch(Message & m);
        
    public:
        Server(const char * listen_hostname,const char * listen_port);
        void dec_count(Message m);
        void serveRequest();
        ~Server();
};
#endif 
