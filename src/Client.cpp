#include "../headers/Client.h"

Client::Client(const char * hostname, const char * port){
        std::string serverIp = hostname_to_ip((char *)hostname);
        reqReply = new RequestReply(port, serverIp.c_str(), true, true, 1024);
}

void Client::executePrompt(){
      do {
        printf("Enter message:");
        scanf("%s", buffer );

        reqReply->doOperation(buffer);
        if(reqReply->getRequest(buffer) >= 0){
                printf("%s \n", buffer); //reply from server
        }
       } while (strcmp(buffer,"q") !=0);
       reqReply->shutDownFD();
}

int Client::execute(char *msg){
        int replyStatus, requestStatus; 
        std::strcpy(buffer, msg);
        requestStatus = reqReply->doOperation(buffer);
        std::cout << requestStatus << std::endl;
        if (requestStatus >= 0){
                if((replyStatus = reqReply->getRequest(buffer)) >= 0){
                        printf("%s \n", buffer); //reply from server
                }
        }
        return replyStatus;
}
Client::~Client(){
     reqReply->shutDownFD();
}