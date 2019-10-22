#include "../headers/RequestReply.h"
#include "../headers/Message.h"

RequestReply::RequestReply(const char *destinationPort, const char *destinationIp, bool isClient) {

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
    }
}

int RequestReply::doOperation(char buffer []){

    Message m = Message(buffer, strlen(buffer));
    m.setMessageType(MessageType(Request));
    char * marshalled = m.marshal();

    int sendStatus = static_cast<int>(sendto(socketfd, marshalled, 1024, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr)));
    if(sendStatus<0) {
        perror ("Send Failed with status ");
    }
    return sendStatus;
}

int RequestReply::getRequest(char buffer []) {

    int recStatus = recvfrom(socketfd,buffer,1024,0,(struct sockaddr*)&si_other, &addr_size);
    Message m = Message(buffer);    
    std::strcpy(buffer, (char *) m.getMessage()); 

    if(recStatus<0) {
        perror("Could not Receive Message with status ");
    }

    return recStatus;
}


int RequestReply::sendReply(char buffer []) {
    
    Message m = Message(buffer, strlen(buffer));
    m.setMessageType(MessageType(Reply));
    char * marshalled = m.marshal();

    int replyStatus = sendto(socketfd, marshalled, 1024, 0, (struct sockaddr*)&si_other, sizeof(si_other));
    if(replyStatus<0)
    {
        perror("Could not Reply to Sender with status ");
    }

    return replyStatus;
}

void RequestReply::shutDownFD() {
    shutdown(socketfd , SHUT_RDWR);
}