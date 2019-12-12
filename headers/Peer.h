
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

    Database * db;

    std::thread serveThread;

    RequestReply* reqRep;

    Message buildRequest(serviceOperations operation, int image_id);
public:
    Peer(const char *myIp, std::string myName, std::string dosIp);
    ~Peer();

    std::string authenticate(std::string username, std::string password);
    std::string login(std::string username, std::string password);
    void getSamplesFromDoS();

    void sendMyProfile(bool toDoS, std::string destIp, int PORT);


    int requestImageFromPeer(int imgId, const char *destPeerIp);
    int requestProfileFromPeer(const char *destPeerIp);
    void updateViewsForPeer(int image_id, int new_count, std::string user_name, const char * peerIp);
    int viewImage(int image_id, std::string user_name);

    void dispatch(Message  msg);
    void serveRequst();

    std::string getMyIP();
    std::string getMyName();

    void Accept(std::string msg_id);
    void Reject(std::string msg_id);
    std::vector<Message> getPending();

    std::map<std::string, int> getImageInfo(int img_id);

    // Communication
    Message sendMsg(DOS_OPERATIONS operation, const char *destIp, int destPort,
                    std::string msg, RequestReply *rrp, int listenPort, int SEND_OR_RECEIVE);

    Message receiveMsg(const int PORT);

    void join();
};


#endif //DISTRIBUTEDC_PEER_H
