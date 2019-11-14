//
// Created by Mazen on 14.11.19.
//

#ifndef DISTRIBUTEDC_DOS_H
#define DISTRIBUTEDC_DOS_H


#include <map>
#include <netinet/in.h>

class DoS {
private:

    struct Transaction{
        int server_fd;
        sockaddr_in address;
    };
    Transaction authTx;
    Transaction loginTx;

    std::map<std::string, std::string> db;
    Transaction init_socket(int LISTEN_PORT);
    void listenTx(Transaction tx, char* req);

public:
    DoS(int AUTH_PORT, int LOGIN_PORT);
    void DoS::runLoginSys();
    void DoS::runAuthSys();
};


#endif //DISTRIBUTEDC_DOS_H
