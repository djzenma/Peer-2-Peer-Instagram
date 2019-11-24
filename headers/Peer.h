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

    std::string authenticate(std::string username, std::string password, std::string dosIp);
    std::string login(std::string username, std::string password, std::string dosIp);
    void sendMyImgs(std::string dosIp);
    std::vector<Message> getSamples(int n);
};


#endif //DISTRIBUTEDC_PEER_H
