
#ifndef DISTRIBUTEDC_COMMUNICATION_H
#define DISTRIBUTEDC_COMMUNICATION_H

#include <printf.h>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include <cmath>
#include <netinet/in.h>
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
    long read_size, total_size;

public:
    static const int buffer_size = 2000;
    char send_buffer[buffer_size];

    Communication();


    Transaction authTx;
    Transaction loginTx;
    Transaction msgIdTx;
    Transaction dbTx;
    Transaction peerDBTx;


    void reset();
    Transaction init_socket(const char *LISTEN_IP, const int LISTEN_PORT);
    int listenTx(Transaction& tx, char* req);

    char* comMsg(const char *destIP, const int destPort, char *msg, int send_receive);
    Message buildImageMsg(int image_id, std::string owner_ip, std::string owner_name);
    int getImage( bool & single ,Message &m, int receivingPort, std::string receiverIP, std::string directory);
    int sendImage(Message &m, std::string destIp, int destPort);
};


#endif //DISTRIBUTEDC_COMMUNICATION_H