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
    std::string myIp, myName, dosIp;
public:
    Peer(std::string myIp, std::string myName, std::string dosIp);

    std::string authenticate(std::string username, std::string password);
    std::string login(std::string username, std::string password);
    void sendMyImgs();
    std::vector<Message> getSamples(int n);
};


#endif //DISTRIBUTEDC_PEER_H
