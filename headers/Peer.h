#ifndef DISTRIBUTEDC_PEER_H
#define DISTRIBUTEDC_PEER_H


#include <string>
#include <thread>
#include <iostream>
#include <stdio.h>
#include "RequestReply.h"
#include "Communication.h"
#include "Image.h"
#include "Database.h"
#include "Stego.h"

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


        int requestImageFromPeer(int imgId, const char *destPeerIp);
        int requestProfileFromPeer(const char *destPeerIp);
        void updateViewsForPeer(int image_id, int new_count, std::string user_name, const char * peerIp);
        int viewImage(int image_id, std::string & path);
        void requestMoreViews(int image_id, const char * destPeerIp);
        
        void dispatch(Message  msg);
        void serveRequst();

        std::string getMyIP();
        std::string getMyName();

        void Accept(std::string msg_id);
        void Reject(std::string msg_id);
        std::vector<Message> getPending();

        std::map<std::string, int> getImageInfo(int img_id);

    void join();
};


#endif //DISTRIBUTEDC_PEER_H