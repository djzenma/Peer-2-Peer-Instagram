#include "../headers/Server.h"

Server::Server(const char *destinationPort, const char *destinationIp) {
    RequestReply * reqReply = new RequestReply(destinationPort, destinationIp, false);
    do {
        if(reqReply->getRequest(buffer) >= 0)
            printf("Data Recieved: %s \n",buffer); // msg received
        reqReply->sendReply(buffer);
    } while (strcmp(buffer,"q") !=0);
    reqReply->shutDownFD();
}