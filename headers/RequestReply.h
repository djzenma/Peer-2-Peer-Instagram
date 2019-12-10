#ifndef REQUESTREPLY_H
#define REQUESTREPLY_H

#include <cstdlib>
#include <netinet/in.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <arpa/inet.h>
#include <iostream>
#include <cmath>
#include <thread>
#include <vector>
#include <mutex>
#include <map>
#include "Message.h"

#define NUM_RETRIES 8
#define BUFF_SIZE 9216

struct argsSend{
    std::vector<Message> packets;
    std::string IP;
    int port;
    int res;
    bool isEmpty;
};

class RequestReply {
    private:
        int port, socketfd , newsockfd;
        socklen_t  clilen;
        struct sockaddr_in serverAddr, si_other;
        bool isClient;
        int buff_size;
        socklen_t addr_size;
    
        struct hostent *server;
        long stat, packet_index, read_size = -1,total_size = 0  ,size ;
        char  read_buffer[BUFF_SIZE];
        
        std::string myIP;

        argsSend a;
        
        std::map<std::string , std::pair<Message, bool>> rec_buffer;

        std::thread sendThread, recThread;
        std::mutex mlock;
        std::mutex ack_lock;

        std::map<std::string, std::pair<int, std::vector<Message>>> chunked_msgs; // <request_id, message>
        std::map<std::string, Message> acks;
        std::vector<Message> createPackets(Message& m);

    public:

        RequestReply(const char * host_ip, const int PORT);
        
        void send(argsSend a);
        std::string sendMessage(Message & m, const char* IP, const int PORT);

        void rec();
        int recReply(Message & m, std::string request_id);
        int recRequest(Message & m);
        
        bool recieveACK(std::string ack_id, Message & ack_msg);

        void Accept(std::string msg_id);
        void Reject(std::string msg_id);

        std::vector<Message> getPending();

        void shutDownFD();


};
#endif
