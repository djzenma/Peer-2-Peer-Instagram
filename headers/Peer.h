
#ifndef DISTRIBUTEDC_PEER_H
#define DISTRIBUTEDC_PEER_H


#include <string>
#include <thread>
#include "Database.h"
#include "RequestReply.h"
#include "utils.h"
#include <json/json.h>


class Peer {
private:
    std::string myIp, myName, dosIp;
    std::thread msgIdThread;
    Database * db;

    RequestReply* reqRep;
    //RequestReply* reqRepAuth;
    //RequestReply* reqRepAuth;

    void runMsgIdThread();
    void runMsgIdSys();

public:
    Peer(const char *myIp, std::string myName, std::string dosIp);

    std::string authenticate(std::string username, std::string password);
    std::string login(std::string username, std::string password);
    void getSamplesFromDoS();

    void sendMyProfile(bool toDoS, std::string destIp, int PORT);
    void requestProfileFrom(std::string destIp, bool robot);

    Message requestImageFromPeer(int imgId, const char *destPeerIp);
    void sendImageToPeer(Message &m ,std::string destIp, int destPort ) ;

    void listenForDBRequests (const char * destIp);
    std::vector<Message>getDbFromDoS(int n) ;
    void getDB (const char *robotIp );

    std::string getMyIP();
    std::string getMyName();

    // Communication
    Message sendMsg(DOS_OPERATIONS operation, const char *destIp, int destPort,
                    std::string msg, RequestReply *rrp, int listenPort, int SEND_OR_RECEIVE);

    Message receiveMsg(const int PORT);

    void join();
};


#endif //DISTRIBUTEDC_PEER_H
