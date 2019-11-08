#include "../headers/Server.h"

Server::Server(const char * hostname, const char * port){
    std::string serverIp = hostname_to_ip((char *)hostname);
    reqReply = new RequestReply(port, serverIp.c_str(), false, false, 1024);
}
void Server::setBufferSize(int size){
    /*delete buffer;
    buffer = new char [buff_size];
    reqReply->setBuffSize(buff_size);*/
}

void Server::serveRequest(){
    printf("Enter Image Path:");
    scanf("%s", buffer );

  reqReply->doOperation(buffer);
}

Server::~Server(){
    reqReply->shutDownFD();

}