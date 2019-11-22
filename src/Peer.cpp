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



void Peer::authenticate(std::string username, std::string password, std::string dosIp) {
    std::string cred = username + "/" + password;

    char* cred_char = const_cast<char *>(cred.c_str());
    const char* dosIp_char = dosIp.c_str();

    char* res = com->sendMsg(dosIp_char, AUTH_PORT, cred_char);
    if(strcmp(res, "ok") == 0) {
        sendMyImgs(dosIp);
    }

}


void Peer::login(std::string username, std::string password, std::string dosIp) {
    std::string cred = username + "/" + password;

    char* cred_char = const_cast<char *>(cred.c_str());
    const char* dosIp_char = dosIp.c_str();

    com->sendMsg(dosIp_char, LOGIN_PORT, cred_char);
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