
//
// Created by Mazen on 21.10.19.
//
#ifndef REQUESTREPLY_H
#define REQUESTREPLY_H

#include <cstdlib>
#include <netinet/in.h>
#include <cstdio>
#include <cstring>
#include <arpa/inet.h>
#include <iostream>


class RequestReply {
    private:
        int port, socketfd , newsockfd;
        socklen_t addr_size  , clilen;
        struct sockaddr_in serverAddr, cli_addr;
        bool isClient;
        bool isTimeout;
        int buff_size;
        //////////
        struct hostent *server;
        FILE *picture;
        long stat, packet_index, read_size, size ;
        char send_buffer[10240], read_buffer[256];

    public:

        RequestReply(const char *destinationPort, const char *destinationIp, bool isClient, bool isTimeout, int buff_size);

        int doOperation(char buffer []);
        int getRequest(char buffer []);
        int getReply(char buffer []);
        int sendReply(char buffer []);
        void shutDownFD();

        void setBuffSize(int);
};
#endif