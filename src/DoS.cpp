//
// Created by Mazen on 14.11.19.
//

#include <iostream>
#include "../headers/DoS.h"

DoS::DoS(const char *LISTEN_IP, const int AUTH_PORT, const int LOGIN_PORT) {
    authTx = init_socket(LISTEN_IP, AUTH_PORT);
    loginTx = init_socket(LISTEN_IP, LOGIN_PORT);
}


// socket creation & binding
// Returns socketfd, address
DoS::Transaction DoS::init_socket(const char *LISTEN_IP, const int LISTEN_PORT) {
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }


    // Forcefully attaching socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(LISTEN_IP);
    //address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( LISTEN_PORT );

    // Forcefully attaching socket to the port
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    Transaction tx;
    tx.address = address;
    tx.server_fd = server_fd;
    return tx;
}

/*
 * Listen For Login Requests
 */
#pragma clang diagnostic push // Ignore Infinite Loop
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void DoS::runLoginSys() {
    int new_socket;
    char req[1024] = {0};
    Credentials credentials;
    std::map<std::string, std::string>::iterator it;
    char *res;

    while(true) {
        new_socket = listenTx(loginTx, req);
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
    char req[1024] = {0};
    Credentials credentials;

    while(true) {
        new_socket = listenTx(authTx, req);
        std::cout<<"DoS: Auth request= "<<req<<"\n";
        credentials = getCredentials(req);
        db.insert({credentials.user, credentials.pass});

        send(new_socket , "ok" , strlen("ok") , 0 );
        std::cout<<"DoS: Credentials for "<< credentials.user << " inserted.\n";
    }
}
#pragma clang diagnostic pop


/*
 * Listen For Requests
 */
int DoS::listenTx(DoS::Transaction tx, char* req) {
    int new_socket, valread;
    int addrlen = sizeof(tx.address);

    if (listen(tx.server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(tx.server_fd, (struct sockaddr *)&tx.address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    valread = read( new_socket , req, 1024);
    return new_socket;
}

void DoS::runLoginThread() {
    loginThread = std::thread(&DoS::runLoginSys, this);
}

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
