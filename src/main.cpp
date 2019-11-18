#include<iostream>

#include "../headers/Client.h"
#include "../headers/Server.h"
#include "../headers/DoS.h"
#include "../headers/Database.h"
#include <pthread.h>
#include <string>
using namespace std;

#define NUM_THREADS 2
const char* hostname ;
const char* port ;

void *client_thread(void *threadid) {
    Client * c = new Client(hostname, port);
    c->executePrompt();
}

void *server_thread(void *threadid) {
    Server* s = new Server(hostname, port);
    s->serveRequest();
}


int main(int argc,char **argv){

    pthread_t threads[NUM_THREADS];
    hostname = argv[2] ;
    port = argv[1] ;
    int rc;


    if(strcmp(argv[3], "client") == 0) { // equal doesn't work

        rc = pthread_create(&threads[0], NULL, client_thread, (void *) 0);

        if (rc) {
            cout << "Error:unable to create thread," << rc << endl;
            exit(-1);
        }
        pthread_exit(NULL);
    }
    else if(strcmp(argv[3], "server") == 0)
    {
        rc = pthread_create(&threads[1], NULL, server_thread, (void *) 1);

        if (rc) {
            cout << "Error:unable to create thread," << rc << endl;
            exit(-1);
        }
        pthread_exit(NULL);
    }
    else {// DoS
        /*
         * argv[1] = Auth Port, argv[2] = Login Port, argv[3] = IP
         */
        auto dos = new DoS(argv[3], stoi(argv[1]), stoi(argv[2]));
        dos->runAuthThread();
        dos->runLoginThread();
        dos->join();
    }
    return 0;
}

