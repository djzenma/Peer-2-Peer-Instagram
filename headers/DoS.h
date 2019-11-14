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

class DoS {
private:

    struct Transaction{
        int server_fd;
        sockaddr_in address;
    };
    Transaction authTx;
    Transaction loginTx;

    std::thread loginThread;
    std::thread authThread;

    std::map<std::string, std::string> db;
    Transaction init_socket(const char * LISTEN_IP, int LISTEN_PORT);
    int listenTx(Transaction tx, char* req);

public:
    DoS(const char * LISTEN_IP, int AUTH_PORT, int LOGIN_PORT);
    void runLoginSys();
    void runAuthSys();
    void runLoginThread();
    void runAuthThread();
    void join();

    virtual ~DoS();
};


#endif //DISTRIBUTEDC_DOS_H
