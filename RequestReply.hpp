//
// Created by Mazen on 21.10.19.
//
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

public:

    RequestReply(const char *destinationPort, const char *destinationIp, bool isClient) {
        port = atoi(destinationPort);
        char buffer [1024];
        memset(&serverAddr,'\0',sizeof(serverAddr));

        serverAddr.sin_family=AF_INET;
        serverAddr.sin_port=htons(port);
        serverAddr.sin_addr.s_addr = inet_addr(destinationIp);

        if(isClient)
            socketfd = socket(PF_INET,SOCK_DGRAM,0);
        else {
            socketfd = socket(AF_INET,SOCK_DGRAM,0);
            bind(socketfd, (struct sockaddr*)  &serverAddr, sizeof(serverAddr));
            addr_size = sizeof(si_other);
        }

        if(socketfd  <0) {
            perror("socket failed");
            //throw "Socket Failed with status "+socketfd;
        }
    }

    int doOperation(char buffer []){
        int sendStatus = static_cast<int>(sendto(socketfd, buffer, 1024, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr)));
        if(sendStatus<0) {
            //throw "Send Failed with status "+sendStatus;
            perror ("Send Failed with status ");
        }
        return sendStatus;

    }

    int getRequest(char buffer []) {
        int recStatus = recvfrom(socketfd,buffer,1024,0,(struct sockaddr*)&si_other, &addr_size);
        if(recStatus<0) {
            perror("Could not Receive Message with status ");
            //throw "Could not Receive Message with status "+recStatus;
        }

        return recStatus;
    }


    int sendReply(char buffer []) {
        int replyStatus = sendto(socketfd, buffer, 1024, 0, (struct sockaddr*)&si_other, sizeof(si_other));
        if(replyStatus<0)
        {
            //throw "Could not Reply to Sender with status " + replyStatus;
            perror("Could not Reply to Sender with status ");
        }

        return replyStatus;
    }

    void shutDownFD() {
        shutdown(socketfd , SHUT_RDWR);
    }
};