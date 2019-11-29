//
// Created by Mazen on 16.11.19.
//

#ifndef DISTRIBUTEDC_COMMUNICATION_H
#define DISTRIBUTEDC_COMMUNICATION_H

#include <netinet/in.h>
#include <printf.h>
#include <arpa/inet.h>
#include <cstring>
#include <zconf.h>
#include <cstdlib>
#include <cmath>
#include "Message.h"

class Communication {
private:

    struct Transaction{
        int server_fd;
        sockaddr_in address;
    };


    int sock;
    // Imaging using ReqReply
    int socketfd;
    struct sockaddr_in peerAddr;
    struct hostent * peer;
    long stat, read_size, total_size;

public:
    static const int buffer_size = 2000;
    char send_buffer[buffer_size];

    Communication();


    Transaction authTx;
    Transaction loginTx;

    void reset();
    int init_socket(const char *LISTEN_IP, int LISTEN_PORT);
    int init_imaging_socket(std::string dest_ip);
    int listenTx(int socket_fd, sockaddr_in address, char* req);

    char* comMsg(const char *destIP, const int destPort, char *msg, int send);

    Message buildImageMsg(int image_id, std::string owner_ip, std::string owner_name);
    int getImage(Message &m, int receivingPort) ;
    int sendImage(Message &m, std::string destIp, int destPort);
};


#endif //DISTRIBUTEDC_COMMUNICATION_H