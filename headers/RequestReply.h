
#ifndef REQUESTREPLY_H
#define REQUESTREPLY_H

#include <cstdlib>
#include <netinet/in.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <arpa/inet.h>
#include <iostream>


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
        char send_buffer[10240], blurr_buffer[10240] ,read_buffer[256];

    public:

        RequestReply(const char *destinationPort, const char *destinationIp, bool isClient,  int buff_size);

        int doOperation(std::string s);
         int getRequest(std::string s);
        int getReq(int & reqNum);
        int sendReq(int reqNum);
        int getMessage(std::string & msg);
        int sendMessage(std::string msg);
        void shutDownFD();

        void setBuffSize(int);
};
#endif