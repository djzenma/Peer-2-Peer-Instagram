#include<iostream>

#include "../headers/Client.h"
#include "../headers/Server.h"
#include "../headers/DoS.h"
<<<<<<< HEAD
#include "../headers/Database.h"
#include <pthread.h>
#include <string>
=======
#include "../headers/Communication.h"

>>>>>>> 0e5ecd2388631a12ef5cc0c5ce0d97407971cd95
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


<<<<<<< HEAD
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
=======
int main(int argc,char **argv){  
      
    if(strcmp(argv[3], "client") == 0){ // equal doesn't work
        Client * c = new Client(argv[2], argv[1]);
        /*if (argc > 4){
           // client load <num_reqs>
           int num_req = atoi(argv[5]);
           varyLoad(c,num_req);
        }
        else*/
          c->executePrompt();

>>>>>>> 0e5ecd2388631a12ef5cc0c5ce0d97407971cd95
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

