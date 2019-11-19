
#ifndef REQUESTREPLY_H
#define REQUESTREPLY_H

#include <cstdlib>
#include <netinet/in.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <arpa/inet.h>
#include <iostream>
#include <math.h>

#include "Stego.h"
#include "Message.h"

class RequestReply {
    private:
        int port, socketfd , newsockfd;
        socklen_t  clilen;
        struct sockaddr_in serverAddr, cli_addr;
        bool isClient;
        int buff_size;
        //////////
        struct hostent *server;
        FILE *picture, *picture2;
        long stat, packet_index, read_size = -1,total_size = 0  ,size ;
        char send_buffer[10240] ,read_buffer[10240];


    public:

        RequestReply(const char *destinationPort, const char *destinationIp, bool isClient,  int buff_size);
        
        int sendReply(Message & m); //sends the image
        int getReply(Message & m); //gets the image
        int sendReq(Message & m); //sends reqnum
        int getReq(Message & m); //gets reqnum

        int Accept ();
        int getMessage(std::string & msg);//sends message
        int sendMessage(std::string msg);
        void shutDownFD();

};
#endif