
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
#include "utils.h"
#include <sys/stat.h>
#include "RequestReply.h"

enum PORTS {
    AUTH_PORT = 4040,
    LOGIN_PORT = 4041,
    DB_PORT = 4042,
    ROBOT_PORT = 4043,//TODO
    PEER_DEFAULT_PORT = 5052,
    PEER_IMAGES_PORT = 5050,
    PEER_IMAGES_ID_PORT = 5050,
};
enum FLAGS {
    SEND = 0,
    RECEIVE = 1,
    SEND_RECEIVE = 2
};

struct Profile{
    std::string user, pass, ip;
};

class DoS {
private:


    // DoS IP, auth_fd, login_fd
    const char *dosIp;
    int auth_fd, login_fd;

    // Communication Module
    Communication *com;
    int new_socket, login_socket;

    RequestReply* reqRep;

    // Threads
    std::thread loginThread;
    std::thread authThread;
    std::thread dbThread;

    // Database
    std::map<std::string, std::string> activeUsers;


    Profile getAllImages(Message profile);

    // Helper functions
    Profile getCredentials(std::string request);

    void sendSamples(std::string owner_ip, std::string owner_name);
    std::string getIP(struct sockaddr_in addr);
    std::map<std::string, std::string> db;

    void insertInDB(Profile credentials, std::string ip);

    void getCredentials_And_NumImgs(Profile& profile, int& imgs, std::string msg);

public:
    explicit DoS(const char * dosIp);
    void runLoginSys();
    void runAuthSys();
    void runLoginThread();
    void runAuthThread();
    void join();
    void runDBThread();
    void runDBSys();

    Profile retrieveUserDB(std::string hostname);


    virtual ~DoS();

};

#endif //DISTRIBUTEDC_DOS_H
