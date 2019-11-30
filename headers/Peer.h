//
// Created by Mazen on 21.11.19.
//

#ifndef DISTRIBUTEDC_PEER_H
#define DISTRIBUTEDC_PEER_H


#include <string>
#include <thread>
#include "Communication.h"

class Peer {
private:
    Communication *com;
    std::string myIp, myName, dosIp;
    std::thread msgIdThread;

    void runMsgIdThread();
    void runMsgIdSys();
public:
    Peer(const char *myIp, std::string myName, std::string dosIp);

    std::string authenticate(std::string username, std::string password);
    std::string login(std::string username, std::string password);
    void sendMyProfile(bool toDoS, std::string destIp);
    std::vector<Message> getSamplesFromDoS(int n);
    Message requestImageFromPeer(int imgId, const char *destPeerIp);

    std::string getMyIP();
    std::string getMyName();

    void join();
};


#endif //DISTRIBUTEDC_PEER_H
