#include<iostream>

#include "../headers/Client.h"
#include "../headers/Server.h"
#include "../headers/DoS.h"
#include "../headers/Database.h"
#include <pthread.h>
#include <string>
#include <unordered_map>
#include "../headers/Communication.h"

using namespace std;

#define NUM_THREADS 2
pthread_t threads[NUM_THREADS];
const char* hostname ;
const char* port ;
bool serv = false ;


void  server_thread() {
    Server* s = new Server(hostname, port); //needs to connect to client thus gets ip and port from argsv
    s->serveRequest();
    pthread_cancel(threads[1]);
    pthread_exit(NULL);
}


void client_thread() {
    Client * c = new Client("127.0.0.1", "4040"); //always run on local ip
    while(1) {
        cout << "Do You want to Switch to Server? "  ;
        cin >> serv ;
        if (serv == true)
        {
            std::thread t1 (server_thread);
            t1.join();
        }
        else
            c->executePrompt();
    }
}
int main(int argc,char **argv){

    hostname = argv[2] ;
    port = argv[1] ;
    int rc;


    if(strcmp(argv[3], "client") == 0) { // equal doesn't work

        std::thread t0 (client_thread);
        t0.join();

    }
    else if(strcmp(argv[3], "server") == 0)
    {
        std::thread t1 (server_thread);
        t1.join();

    }
    else {// DoS
        /*
         * argv[1] = Auth Port, argv[2] = Login Port, argv[3] = IP
         */
        const char* auth_port = argv[1];
        const char* login_port = argv[2];
        const char* ip = argv[3];

        bool client_tst = true;
        if (client_tst) {
            auto com = new Communication();
            com->sendMsg(ip, stoi(auth_port), "Mazen/123");
            com->sendMsg(ip, stoi(login_port), "Mazen/123");
        }
        else {
            auto dos = new DoS(ip, stoi(auth_port), stoi(login_port));
            dos->runAuthThread();
            dos->runLoginThread();
            dos->join();
        }
    }
    return 0;
}

