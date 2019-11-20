//#include<iostream>

#include "../headers/Client.h"
#include "../headers/Server.h"
#include "../headers/DoS.h"
#include "../headers/Database.h"
#include <pthread.h>
#include <thread>
#include <string>
#include "../headers/Communication.h"
#include "../headers/Stego.h"

using namespace std;

#define NUM_THREADS 2
pthread_t threads[NUM_THREADS];
const char* hostname ;
const char* port ;
bool cli = false ;
string h , p ;

void client_thread() {
    Client * c = new Client(hostname, port); //always run on local ip
            c->executePrompt();

    pthread_cancel(threads[1]);
    pthread_exit(NULL);

}

void  server_thread() {
    Server* s = new Server("127.0.0.1", "4040"); //needs to connect to client thus gets ip and port from argsv
    while(1) {
        cout << "Do You want to Switch to Client? ";
        cin >> cli;
        if (cli == true) {
            cout <<"Who do You want to Connect to (Ip)"; //from Dos
            cin >> h ;
            cout <<"Who do You want to Connect to (Port)"; //from Dos
            cin >> p ;

            port = p.c_str() ;
            hostname = h.c_str();

            std::thread t1(client_thread);
            t1.join();
        } else
            s->serveRequest();
    }
}

int main(int argc,char **argv){


    if(argc > 1 &&strcmp(argv[1], "dos") == 0)
    {// DoS
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
    } else
    {
        std::thread t1 (server_thread);
        t1.join();

    }
    return 0;
}

