//
// Created by Mazen on 14.11.19.
//

#include <iostream>
#include <cmath>
#include <algorithm>
#include "../headers/DoS.h"


DoS::DoS(const char *dosIp) {
    this->dosIp = dosIp;
    com = new Communication();
    com->authTx = com->init_socket(dosIp, AUTH_PORT);
    com->loginTx = com->init_socket(dosIp, LOGIN_PORT);
}



/*
 * Listen For Login Requests
 */
#pragma clang diagnostic push // Ignore Infinite Loop
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void DoS::runLoginSys() {
    int new_socket;
    char req[2000] = {0};
    Credentials credentials;
    std::map<std::string, std::string>::iterator it;
    char *res;
    sockaddr_in peerAddress;

    std::cout<<"DoS: Listening for Login\n";
    while(true) {
        //Message msg;
        com->loginTx = com->listenTx(com->loginTx, req);
        std::cout<<"DoS: Login request= "<<req<<"\n";
        credentials = getCredentials(req);

        try {
            db.at(credentials.user);
            res = const_cast<char *>("ok");
        } catch (std::out_of_range& exception) {
            res = const_cast<char *>("refused");
        }

        sendto(com->loginTx.server_fd, "ok", strlen("ok"), 0, (struct sockaddr*)&com->loginTx.address, sizeof(com->loginTx.address));
        //send(login_socket , res , strlen(res) , 0);
        std::cout<<"DoS: sent: "<<res<<"\n";
    }
}
#pragma clang diagnostic pop



/*
 * Listen For Authentication Requests. Steps:
 * 1. Peer Authenticates
 * 2. Peer sends all his photos
 * 3. Peer requests number of samples, DoS sends them
 */
#pragma clang diagnostic push   // Ignore Infinite Loop
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void DoS::runAuthSys() {
    Credentials credentials;

    std::cout<<"DoS: Listening for Auth...\n";
    while(true) {
        char req[2000] = {0};
        //Message msg;
        // Listening For Authentication
        com->authTx = com->listenTx(com->authTx, req);
        std::cout<<"DoS: Peer IP: "<<getIP(com->authTx.address)<<"\n";

        if(strcmp(req, "samples") == 0) {   // 3. Send peer number of samples to be sent, then send them
            std::cout << "DoS: Sending number of samples...\n";
            int n = 2;
            sendto(com->authTx.server_fd, "1", strlen("1"), 0, (struct sockaddr*)&com->authTx.address, sizeof(com->authTx.address));
            //send(new_socket, "1", strlen("1"), 0);

            // Send him All Samples
            std::string peerIp = getIP(com->authTx.address);
            std::cout << "Sending Samples to IP: " << peerIp << "\n";
            sendSamples(peerIp, credentials.user);
        }
        else if(!is_number(req)) {   // 1. Authentication request
            // Got request
            std::cout<<"DoS: Auth request= "<<req<<"\n";
            credentials = getCredentials(req);

            // Add peer credentials to db
            db.insert({credentials.user, credentials.pass});

            // Send ok Response
            sendto(com->authTx.server_fd, "ok", strlen("ok"), 0, (struct sockaddr*)&com->authTx.address, sizeof(com->authTx.address));
            //send(new_socket , "ok" , strlen("ok") , 0);
        }
        else {  // 2. Peer Sends all his photos, req = number of photos
            std::cout<<"DoS: Num of Images to be received: "<<req<<"\n";
            // Send ok Response (ok send me your photos)
            sendto(com->authTx.server_fd, "ok", strlen("ok"), 0, (struct sockaddr*)&com->authTx.address, sizeof(com->authTx.address));
            //send(new_socket , "ok" , strlen("ok") , 0);

            // Receive his photos
            std::string peerIp = getIP(com->authTx.address);
            std::vector<Message> images;
            images = getAllImages(std::stoi(req));

            // Insert him to the Active users List and save his IP
            activeUsers.insert({credentials.user, peerIp});
            std::cout<<"DoS: User "<< credentials.user << " added to the active list.\n";
        }
    }
}
#pragma clang diagnostic pop


std::vector<Message> DoS::getAllImages(int n) {
    std::cout<<"DoS: Receiving Peer's " <<n<<" Images...\n";
    std::vector<Message> images;
    for (int i=0; i<n; i++) {
        Message image;
        com->getImage(image, AUTH_PORT, dosIp);
        images.push_back(image);
    }
    std::cout<<"DoS: Peer Images Received!\n";
    return images;
}


void DoS::sendSamples(std::string owner_ip, std::string owner_name) {
    //com->init_imaging_socket(getIP(com->authTx.address));
    std::cout<<"DoS: Sending Samples to the Peer...\n";
    for (int i = 0; i < 1; i++) {
        sleep(1);
        Message msg = com->buildImageMsg(i, owner_ip, owner_name);
        com->sendImage(msg, owner_ip, PEER_IMAGES_PORT);
    }
    std::cout<<"DoS: Samples Sent!\n";
}


// Return IP from Address
std::string DoS::getIP(struct sockaddr_in addr) {
    return inet_ntoa(addr.sin_addr);
}



DoS::Credentials DoS::getCredentials(std::string request) {
    std::string delimiter = "/";
    Credentials credentials;

    size_t pos = 0;
    std::string token;
    while ((pos = request.find(delimiter)) != std::string::npos) {
        token = request.substr(0, pos);
        credentials.user = token;
        request.erase(0, pos + delimiter.length());
    }
    credentials.pass = request;

    return credentials;
}

bool DoS::is_number(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

/*
 * Only runs the Login thread
 */
void DoS::runLoginThread() {
    loginThread = std::thread(&DoS::runLoginSys, this);
}

/*
 * Only runs the Auth thread
 */
void DoS::runAuthThread() {
    authThread = std::thread(&DoS::runAuthSys, this);
}




DoS::~DoS() {
    if (loginThread.joinable())
        loginThread.join();
    if (authThread.joinable())
        authThread.join();
}

void DoS::join() {
    authThread.join();
    loginThread.join();
}