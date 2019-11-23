//
// Created by Mazen on 21.11.19.
//

#ifndef DISTRIBUTEDC_PEER_H
#define DISTRIBUTEDC_PEER_H


#include <string>
#include "Communication.h"

class Peer {
private:
    Communication *com;
    std::string myIp, myName;
public:
    Peer(std::string ip, std::string name);

    void authenticate(std::string username, std::string password, std::string dosIp);
    void login(std::string username, std::string password, std::string dosIp);
    void sendMyImgs(std::string dosIp);
};


#endif //DISTRIBUTEDC_PEER_H
