//
// Created by Mazen on 14.11.19.
//

#ifndef DISTRIBUTEDC_DOS_H
#define DISTRIBUTEDC_DOS_H


#include <map>
#include <netinet/in.h>
#include <thread>
#include <arpa/inet.h>
#include <zconf.h>
#include <string.h>
#include "Stego.h"
#include <vector>
#include "Message.h"
#include "Communication.h"


/*
 * PORTs Interface:
 * 4040
 */
class DoS {
private:


    struct Credentials{
        std::string user, pass;
    };

    // Communication Module
    Communication *com;

    // Threads
    std::thread loginThread;
    std::thread authThread;

    // Database
    std::map<std::string, std::string> db;
    std::map<std::string, std::vector<Message>> activeUsers;


    std::vector<Message> getAllImages(int n, std::string fromIp);

    // Helper functions
    Credentials getCredentials(std::string request);
    bool is_number(const std::string& s);

    void sendSamples(std::string owner_ip, std::string owner_name);

    std::string getIP(struct sockaddr_in addr);

public:
    DoS(const char * LISTEN_IP);
    void runLoginSys();
    void runAuthSys();
    void runLoginThread();
    void runAuthThread();
    void join();

    virtual ~DoS();

};

enum PORTS {
    AUTH_PORT = 4040,
    LOGIN_PORT = 4041,
    PEER_RECEIVE_SAMPLE_PORT = 5050
};

#endif //DISTRIBUTEDC_DOS_H
