#include "../headers/Server.h"

Server::Server(const char * listen_hostname, const char * listen_port){
    buffer = new char [buff_size];
    std::string serverIp = hostname_to_ip((char *)listen_hostname);
    reqReply = new RequestReply(listen_port,  serverIp.c_str(), false, false, buff_size);
}

void Server::setBufferSize(int size){
    delete buffer;
    buffer = new char [buff_size];
    reqReply->setBuffSize(buff_size);
}

void Server::serveRequest(){

        if(reqReply->getRequest(buffer) >= 0)
            //printf("Data Recieved: %s \n",buffer); // msg received
            buffer = "Connected to Server";
        reqReply->sendReply(buffer);

    reqReply->shutDownFD();
}

Server::~Server(){
    delete buffer;
}