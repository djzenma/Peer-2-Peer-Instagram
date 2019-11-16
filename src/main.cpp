#include<iostream>

#include "../headers/Client.h"
#include "../headers/Server.h"
#include "../headers/DoS.h"
#include "../headers/Communication.h"

using namespace std;


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

    }
    else if(strcmp(argv[3], "server") == 0){
        Server* s = new Server(argv[2], argv[1]);
        /*if(argc > 4){
           // server buffer <buff_size>
           int buff_size = atoi(argv[5]);
           varyBuffSize(s,buff_size); 
        }*/
        s->serveRequest();
    }
    else {// DoS
        /*
         * argv[1] = Auth Port, argv[2] = Login Port, argv[3] = IP
         */
        const char* auth_port = argv[1];
        const char* login_port = argv[2];
        const char* ip = argv[3];

        bool client_tst = true;
        if (tst) {
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

