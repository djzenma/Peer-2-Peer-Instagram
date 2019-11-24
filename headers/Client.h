#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <string.h>

#include "RequestReply.h"
#include "headers/Database.h"
#include "utils.h"
#include "Message.h"

class Client {

    private:
        char * buffer;
        int buff_size = 1024;
        RequestReply* reqReply;
        const char * port;
        const char * hostname;
        std::string name ;
        int req ;
        int viewPic ;

        Message buildRequestMsg(serviceOperations operation, int image_id );
        friend std::string generateRequestId(Client * c);

        Database * db;

    public:
        Client(const char* hostname, const char* port);
        int execute(char * msg);
        int executePrompt(int req,int  image_id, int num_views);
        bool decrementView(std::string image);
        void updateCount(int image_id, std::string user_name, int updated_count);

        ~Client();
};
#endif
