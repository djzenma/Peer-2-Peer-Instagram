#include <stdio.h>
#include <string.h>
#include "RequestReply.hpp"

class Client {
private:
    char buffer [1024];

public:
    Client(const char *destinationPort, const char *destinationIp) {
        RequestReply * reqReply = new RequestReply(destinationPort, destinationIp, true);
        do {
            printf("Enter message:");
            scanf("%s", buffer );

            reqReply->doOperation(buffer);
            if(reqReply->getRequest(buffer) >= 0)
                printf("%s \n", buffer); //reply from server

        } while (strcmp(buffer,"q") !=0);
        reqReply->shutDownFD();
    }
};