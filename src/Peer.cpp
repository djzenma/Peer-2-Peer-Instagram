//
// Created by Mazen on 21.11.19.
//

#include "../headers/Peer.h"
#include "../headers/DoS.h"

Peer::Peer(std::string myIp, std::string myName, std::string dosIp) {
    this->myIp = myIp;
    this->myName = myName;
    this->dosIp = dosIp;
    com = new Communication();
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
        sendMyImgs();
        char* samplesNum = com->comMsg(dosIp_char, AUTH_PORT, "samples", SEND_RECEIVE);
        std::vector<Message> samples = getSamples(std::stoi(samplesNum));
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
        sendMyImgs();
        // Get number of samples
        char* samplesNum = com->comMsg(dosIp_char, LOGIN_PORT, "samples", SEND_RECEIVE);
        getSamples(std::stoi(samplesNum));
    }
    return res;
}

void Peer::sendMyImgs() {
    // Send number of images first
    int n = 1;
    const char* dosIp_char = dosIp.c_str();
    char* n_char = const_cast<char *>(std::to_string(n).c_str());
    char* res = com->comMsg(dosIp_char, AUTH_PORT, n_char, SEND_RECEIVE);

    if(strcmp(res, "ok") == 0) {    // Send the images
        sleep(5);
        std::cout<<"Peer: Sending my images...\n";
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

std::vector<Message> Peer::getSamples(int n) {
    std::vector<Message> images;
    for (int i=0; i<n; i++) {
        Message image;
        com->getImage(image, PEER_IMAGES_PORT);
        images.push_back(image);
    }

    return images;
}
