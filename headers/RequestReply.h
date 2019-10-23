
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
        int port, socketfd;
        socklen_t addr_size;
        struct sockaddr_in serverAddr, si_other;
        bool isClient;
        bool isTimeout;
        int buff_size;

    public:

        RequestReply(const char *destinationPort, const char *destinationIp, bool isClient, bool isTimeout, int buff_size);

        int doOperation(char buffer []);
        int getRequest(char buffer []);
        int sendReply(char buffer []);
        void shutDownFD();

        void setBuffSize(int);
};
#endif