//
// Created by Mazen on 21.11.19.
//

#include "../headers/Peer.h"
#include "../headers/DoS.h"

Peer::Peer(std::string ip, std::string name) {
    myIp = ip;
    myName = name;
    com = new Communication();
}



std::string Peer::authenticate(std::string username, std::string password, std::string dosIp) {
    std::string cred = username + "/" + password;

    char* cred_char = const_cast<char *>(cred.c_str());
    const char* dosIp_char = dosIp.c_str();

    char* res = com->sendMsg(dosIp_char, AUTH_PORT, cred_char);
    if(strcmp(res, "ok") == 0) {
        std::thread sendImagesThread = std::thread(&Peer::sendMyImgs, this, dosIp);
        //sendMyImgs(dosIp);
    }
    return res;

}


std::string Peer::login(std::string username, std::string password, std::string dosIp) {
    std::string cred = username + "/" + password;

    char* cred_char = const_cast<char *>(cred.c_str());
    const char* dosIp_char = dosIp.c_str();

    char* res = com->sendMsg(dosIp_char, LOGIN_PORT, cred_char);
    if(strcmp(res, "ok") == 0) {
        std::thread sendImagesThread = std::thread(&Peer::sendMyImgs, this, dosIp);
        //sendMyImgs(dosIp);
        // Get number of samples
        char* samplesNum = com->sendMsg(dosIp_char, LOGIN_PORT, "samples");
        getSamples(std::stoi(samplesNum));
    }
    return res;
}

void Peer::sendMyImgs(std::string dosIp) {
    // Send number of images first
    int n = 1;
    const char* dosIp_char = dosIp.c_str();
    char* n_char = const_cast<char *>(std::to_string(n).c_str());
    com->sendMsg(dosIp_char, AUTH_PORT, n_char);

    // Send the images
    for(int i=0; i<n; i++) {
        Message img = com->buildImageMsg(i, myIp, myName);
        //com->init_imaging_socket(dosIp_char);
        //com->sendImage(img);
        com->sendImage(img, dosIp);
    }
}

std::vector<Message> Peer::getSamples(int n) {
    std::vector<Message> images;
    for (int i=0; i<n; i++) {
        Message image;
        //com->getImage(image);
        com->getImage(image);
        images.push_back(image);
    }

    return images;
}
