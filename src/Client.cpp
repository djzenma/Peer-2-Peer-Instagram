#include "../headers/Client.h"

Client::Client(const char * listen_hostname, const char * listen_port){
    buffer = new char [buff_size];
    this->port = listen_port ;
    this->hostname = listen_hostname ;
    std::string serverIp = hostname_to_ip((char *)listen_hostname);
    reqReply = new RequestReply(listen_port,  serverIp.c_str(), true, 1024);
}


void Client::executePrompt() {

    if (!requestNumber (0))
        perror("Error Sending Request Number");
    if (!requestSamples ())
        perror("Error Requesting Samples from Server");


}
int Client :: requestNumber (int req)
{
    printf("\nSending a Request of index: %i\n", req);
    return reqReply->sendReq(req); //sends request number to server
}

int Client :: requestSamples ()
{
    printf("Receiving Samples ...\n");
    return reqReply->getRequest() ; // receives photo
    //reqReply->shutDownFD();
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