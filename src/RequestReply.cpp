#include "../headers/RequestReply.h"
#include "../headers/Message.h"
#include <fcntl.h>


RequestReply::RequestReply(const char *destinationPort, const char *destinationIp, bool isClient, bool isTimeout, int buff_size) {

    port = atoi(destinationPort);

    memset(&serverAddr,'\0',sizeof(serverAddr));

    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(destinationIp);

    if(isClient){
        socketfd = socket(PF_INET,SOCK_DGRAM,0);
        // set timeout on client
        if (isTimeout){
            struct timeval tv;
            tv.tv_sec = 0.5;
            tv.tv_usec = 100;
            setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof (tv));
        }
        
    }
    else {
        socketfd = socket(AF_INET,SOCK_DGRAM,0);
        //fcntl (socketfd, F_SETFL,O_NONBLOCK);
        bind(socketfd, (struct sockaddr*)  &serverAddr, sizeof(serverAddr));
        addr_size = sizeof(si_other);
    }
    
    if(socketfd  <0) {
        perror("socket failed");
    }
    this->isClient = isClient;
    this->isTimeout = isTimeout;
    this->buff_size = buff_size;
}

int RequestReply::doOperation(char buffer []){

    Message m = Message(buffer, strlen(buffer));
    m.setMessageType(MessageType(Request));
    char * marshalled = m.marshal();

    int sendStatus = static_cast<int>(sendto(socketfd, marshalled, buff_size, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr)));

    if (isTimeout){
        int n = 0;
        if (sendStatus<=0)
                n =5;
        while (sendStatus<=0){
            std::cout << "I am trying again "<< std::endl;
            if (n>0){
                sendStatus = static_cast<int>(sendto(socketfd, marshalled, buff_size, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr)));
                n--;
            }
            else {break;}
        }
    }
    
    if(sendStatus<=0) {
        perror("Send Failed with status ");
    }
    return sendStatus;
}

int RequestReply::getRequest(char buffer []) {
    int recStatus = recvfrom(socketfd,buffer, buff_size,0,(struct sockaddr*)&si_other, &addr_size);

    if (isClient && isTimeout){
        int n = 0;
        if (recStatus<=0)
                n =5;
        while (recStatus<=0){
            std::cout << "I am trying again "<< std::endl;
            if (n>0){
                recStatus = recvfrom(socketfd,buffer,buff_size,0,(struct sockaddr*)&si_other, &addr_size);
                n--;
            }
            else {
                break;
            }
        }
    }
   
    if(recStatus<=0) {
        perror("Could not Receive Message with status ");
    }
    else {
        Message m = Message(buffer);    
        std::strcpy(buffer, (char *) m.getMessage());
    }

    return recStatus;
}

void RequestReply::setBuffSize(int size){
    buff_size = size;
}
int RequestReply::sendReply(char buffer []) {
    Message m = Message(buffer, strlen(buffer));
    m.setMessageType(MessageType(Reply));
    char * marshalled = m.marshal();
    int replyStatus = sendto(socketfd, marshalled, buff_size, 0, (struct sockaddr*)&si_other, sizeof(si_other));
    if (isTimeout){
        std::cout<<"timeout reply"<<std::endl;
        int n = 0;
        if (replyStatus<=0)
                n =5;
        while (replyStatus<=0){
            if (n>0){
             replyStatus = sendto(socketfd, marshalled, buff_size, 0, (struct sockaddr*)&si_other, sizeof(si_other));
                n--;
            }
            else {
                break;
            }
        }
    }
   
    if(replyStatus<0)
    {
        perror("Could not Reply to Sender with status ");
    }

    return replyStatus;
}

void RequestReply::shutDownFD() {
    shutdown(socketfd , SHUT_RDWR);
}