#include "../headers/Client.h"



Client::Client(const char * listen_hostname, const char * listen_port){
    buffer = new char [buff_size];
    std::string serverIp = hostname_to_ip((char *)listen_hostname);
    reqReply = new RequestReply(listen_port,  serverIp.c_str(), true, true, 1024);
}


void Client::executePrompt() {
    while (1) {
    reqReply->getReq(reqNum);
        printf("Request Number: %i\n", reqNum);

    }
    //reqReply->getRequest(buffer) ;

}


int Client::execute(char *msg){
        /*int replyStatus, requestStatus;
        std::strcpy(buffer, msg);
        requestStatus = reqReply->doOperation(buffer);
        std::cout << requestStatus << std::endl;
        if (requestStatus >= 0){
                if((replyStatus = reqReply->getReply(buffer)) >= 0){
                        printf("%s \n", buffer); //reply from server
                }
        }
        return replyStatus;*/
}
Client::~Client(){
     reqReply->shutDownFD();
}