//
// Created by Mazen on 14.11.19.
//

#include <iostream>
#include <cmath>
#include "../headers/DoS.h"


DoS::DoS(const char *LISTEN_IP) {
    com = new Communication();
    com->authTx = com->init_socket(LISTEN_IP, AUTH_PORT);
    com->loginTx = com->init_socket(LISTEN_IP, LOGIN_PORT);
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

    std::cout<<"DoS: Listening for Login\n";
    while(true) {

        new_socket = com->listenTx(com->loginTx, req);
        std::cout<<"DoS: Login request= "<<req<<"\n";
        credentials = getCredentials(req);

        try {
            db.at(credentials.user);
            res = const_cast<char *>("ok");
        } catch (std::out_of_range& exception) {
            res = const_cast<char *>("refused");
        }

        send(new_socket , res , strlen(res) , 0);
        std::cout<<"DoS: sent: "<<res<<"\n";
    }
}
#pragma clang diagnostic pop



/*
 * Listen For Authentication Requests
 */
#pragma clang diagnostic push   // Ignore Infinite Loop
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void DoS::runAuthSys() {
    int new_socket;
    Credentials credentials;

    std::cout<<"DoS: Listening for Auth\n";
    while(true) {
        char req[2000] = {0};
        // Listening For Authentication
        new_socket = com->listenTx(com->authTx, req);


        if(!is_number(req)) {   // Authentication request
            // Got request
            std::cout<<"DoS: Auth request= "<<req<<"\n";
            credentials = getCredentials(req);

            // Add peer credentials to db
            db.insert({credentials.user, credentials.pass});

            // Send ok Response
            send(new_socket , "ok" , strlen("ok") , 0);
        }
        else if(strcmp(req, "sample") == 0){
            std::cout<<"DoS: Sending number of samples...\n";
            int n = 2;
            send(new_socket , "2" , strlen("2") , 0);
        }
        else {  // Peer Sends all his photos, req = number of photos
            std::cout<<"DoS: Num of Images to be received: "<<req<<"\n";
            // Send ok Response (ok send me your photos)
            send(new_socket , "ok" , strlen("ok") , 0);


            // Receive his photos
            std::vector<Message> images;
            images = getAllImages(std::stoi(req), getIP(com->authTx.address));

            // Insert him to the Active users List and save his images
            activeUsers.insert({credentials.user, images});

            // Send him All Samples
            std::cout<<"Sending Samples to IP: "<<getIP(com->authTx.address)<<"\n";
            sendSamples(getIP(com->authTx.address), credentials.user);
            std::cout<<"DoS: Credentials for "<< credentials.user << " inserted.\n";
        }
    }
}
#pragma clang diagnostic pop


std::vector<Message> DoS::getAllImages(int n, std::string listenerIP) {
    std::vector<Message> images;
    for (int i=0; i<n; i++) {
        Message image;
        //com->getImage(image);
        com->getImage(image);
        images.push_back(image);
    }

    return images;
}


void DoS::sendSamples(std::string owner_ip, std::string owner_name) {
    com->init_imaging_socket(getIP(com->authTx.address));
    for (int i = 0; i < 1; i++) {
        Message msg = com->buildImageMsg(i, owner_ip, owner_name);
        com->sendImage(msg, owner_ip);
        sleep(5);
    }
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