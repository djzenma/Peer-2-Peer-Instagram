#include <iostream>
#include "RequestReply.hpp"

using namespace std;

class Server {
private:
    char buffer [1024];

public:
    Server(const char *destinationPort, const char *destinationIp) {
        RequestReply * reqReply = new RequestReply(destinationPort, destinationIp, false);
        do {
            if(reqReply->getRequest(buffer) >= 0)
                printf("Data Recieved: %s \n",buffer); // msg received

            reqReply->doOperation(buffer);
        } while (strcmp(buffer,"q") !=0);
        reqReply->shutDownFD();
    }

};