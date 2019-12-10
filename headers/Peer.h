#ifndef DISTRIBUTEDC_PEER_H
#define DISTRIBUTEDC_PEER_H


#include <string>
#include <thread>
#include <iostream>
#include "RequestReply.h"
#include "Communication.h"
#include "Image.h"
#include "Database.h"

class Peer {
    private:
        Communication *com;
        RequestReply * rrp;
        std::string myIp, myName, dosIp;
        std::thread msgIdThread;
        std::thread serveThread;

        Database * db;

        void runMsgIdThread();
        void runMsgIdSys();

        Message buildRequestMsg(serviceOperations operation, int image_id);

    public:
        Peer(const char *myIp, std::string myName, std::string dosIp);
        ~Peer();

        std::string authenticate(std::string username, std::string password);
        std::string login(std::string username, std::string password);
        void sendMyProfile(bool toDoS, std::string destIp);
        std::vector<Message> getSamplesFromDoS(int n);


        int requestImageFromPeer(Message & imgMsg,int imgId, const char *destPeerIp);
        int requestProfileFromPeer(const char *destPeerIp);

        void viewImage(int image_id);
        void updateCountFor(int image_id, int updated_cout,  const char * peerIp);
        
        void dispatch(Message  msg);
        void serveRequst();

        std::string getMyIP();
        std::string getMyName();

        void Accept(std::string msg_id);
        void Reject(std::string msg_id);
        std::vector<Message> getPending();

    void join();
};


#endif //DISTRIBUTEDC_PEER_H