#include "Client.h"

Client::Client(const char *destinationPort, const char *destinationIp) {
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