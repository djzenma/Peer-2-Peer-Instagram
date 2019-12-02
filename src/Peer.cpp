//
// Created by Mazen on 21.11.19.
//

#include "../headers/Peer.h"
#include "../headers/DoS.h"

Peer::Peer(const char *myIp, std::string myName, std::string dosIp) {
    this->myIp = myIp;
    this->myName = myName;
    this->dosIp = dosIp;
    com = new Communication();

    //com->msgIdTx = com->init_socket(myIp, PEER_IMAGES_ID_PORT);
    std::stringstream ss;
    ss << PEER_IMAGES_ID_PORT;

    const char *port = ss.str().c_str();
    reqReplyListener = new RequestReply(port, myIp, false, 1024);
    runMsgIdThread();
}


/*
 * 1. Peer Authenticates
 * 2. Peer sends all his photos
 * 3. Peer requests the number of samples that he will receive
 * 4. Peer receives the samples
 */
std::string Peer::authenticate(std::string username, std::string password) {
    std::string cred = username + "/" + password;

    char* cred_char = const_cast<char *>(cred.c_str());
    const char* dosIp_char = dosIp.c_str();

    // Send my Credentials
    char* res = com->comMsg(dosIp_char, AUTH_PORT, cred_char, SEND_RECEIVE);
    if(strcmp(res, "ok") == 0) {    // If response is ok
        // Send my images
        //std::thread sendImagesThread = std::thread(&Peer::sendMyImgs, this);
        sendMyProfile(true, "");
        char* samplesNum = com->comMsg(dosIp_char, AUTH_PORT, "samples", SEND_RECEIVE);
        std::vector<Message> samples = getSamplesFromDoS(std::stoi(samplesNum));
    }
    return res;

}


std::string Peer::login(std::string username, std::string password) {
    std::string cred = username + "/" + password;

    char* cred_char = const_cast<char *>(cred.c_str());
    const char* dosIp_char = dosIp.c_str();

    char* res = com->comMsg(dosIp_char, LOGIN_PORT, cred_char, SEND_RECEIVE);
    if(strcmp(res, "ok") == 0) {
        //std::thread sendImagesThread = std::thread(&Peer::sendMyImgs, this);
        sendMyProfile(true, "");
        // Get number of samples
        char* samplesNum = com->comMsg(dosIp_char, LOGIN_PORT, "samples", SEND_RECEIVE);
        getSamplesFromDoS(std::stoi(samplesNum));
    }
    return res;
}

void Peer::sendMyProfile(bool toDoS, std::string destIp) {
    // Send number of images first
    int n = 1;  // TODO
    const char* dosIp_char = dosIp.c_str();
    char* n_char = const_cast<char *>(std::to_string(n).c_str());

    if(toDoS) {
        char* res = com->comMsg(dosIp_char, AUTH_PORT, n_char, SEND_RECEIVE);

        if(strcmp(res, "ok") == 0) {    // Send the images
            sleep(5);
            std::cout<<"Peer: Sending my images to DoS...\n";
            for(int i=0; i<n; i++) {
                Message img = com->buildImageMsg(i, myIp, myName);
                com->sendImage(img, dosIp, AUTH_PORT);
                sleep(1);
            }
        }
        else { // DoS didn't answer with ok
            std::cout<<"Peer: DoS didn't answer me when I sent him the number of my photos to be sent\n";
        }
    }
    else {
        std::cout<<"Peer: Sending my images to Peer...\n";
        for(int i=0; i<n; i++) {
            Message img = com->buildImageMsg(i, myIp, myName);
            com->sendImage(img, destIp, PEER_IMAGES_PORT);
            sleep(1);
        }
    }
}

std::vector<Message> Peer::getSamplesFromDoS(int n) {
    std::vector<Message> images;
    for (int i=0; i<n; i++) {
        Message image;
        com->getImage(image, PEER_IMAGES_PORT, myIp);
        images.push_back(image);
    }
    return images;
}

/*
 * Requests an image from a Peer
 */
Message Peer::requestImageFromPeer(int imgId, const char *destPeerIp) {
    std::cout<<"Peer "<<myName<<": requesting image from other Peer!\n";
    char* res = com->comMsg(destPeerIp, PEER_IMAGES_ID_PORT, const_cast<char *>(std::to_string(imgId).c_str()), SEND_RECEIVE);
    if(strcmp(res,"ok") == 0) {
        std::cout<<"Peer "<<myName<<": waiting for the image from other Peer!\n";
        Message image;
        com->getImage(image, PEER_IMAGES_PORT, myIp);
        std::cout<<"Peer "<<myName<<": Image Received Successfully from other Peer!\n";
        return image;
    }
    else
        std::cout<<"Peer: Image not received from other Peer!\n";
}


std::string Peer::getMyIP() {
    return myIp;
}

std::string Peer::getMyName() {
    return myName;
}
/*
 * Run the Msg Id thread
 */
void Peer::runMsgIdThread() {
    msgIdThread = std::thread(&Peer::runMsgIdSys, this);
}

/*
 * Listens for Msg Id requests
 */
#pragma clang diagnostic push   // Ignore Infinite Loop
#pragma clang diagnostic ignored "-Wmissing-noreturn"

void Peer::runMsgIdSys() {
    int new_socket;

    std::cout<<"Peer: Listening for Msg ID requests...\n";
    while(true) {
        char req[2000] = {0};
        Message msg, okMsg;
        okMsg.setMessage("ok", sizeof("ok"));
        sockaddr_in sender;

        // Listening For Msg ID requests
        reqReplyListener->getReq(msg, sender);
        //com->msgIdTx = com->listenTx(com->msgIdTx, req);
        std::cout<<"Peer: Requested Peer IP: ";//<<" Port: "<<reinterpret_cast<const char *>(sender.sin_port)<<std::endl;
        std::string senderIp = getIP(sender);
        std::cout<<senderIp;
        int senderPort = getPort(sender);
        std::cout<<" Port"<<senderPort<<"\n";

        //sendto(com->msgIdTx.server_fd, "ok", strlen("ok"), 0, (struct sockaddr*)&com->msgIdTx.address, sizeof(com->msgIdTx.address));
        sendMsg(getIP(sender), reinterpret_cast<const char *>(sender.sin_port), okMsg);

        // Send him the requested ID
        std::string peerIp = getIP(com->msgIdTx.address);
        std::cout << "Peer: Sending The requested image with ID "<<req<<" to IP: " << peerIp << "\n";
        Message imgMsg = com->buildImageMsg(std::stoi(req), peerIp, myName);
        com->sendImage(imgMsg, peerIp, PEER_IMAGES_PORT);
        std::cout << "Peer "<<myName<<": Finished Sending The requested image with ID "<<req<<" to IP: " << peerIp << "\n";

    }
}
#pragma clang diagnostic pop

void Peer::sendMsg(std::string destIp, const char *destPort, Message m) {
    RequestReply* reqReplySender = new RequestReply(destPort,  destIp.c_str(), true, 1024);
    reqReplySender->sendReq(m);
}

void Peer::join() {
    if (msgIdThread.joinable())
        msgIdThread.join();
}