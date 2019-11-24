#include <thread>
#include "headers/Thread.h"
#include "headers/Server.h"


const char* hostname ;
const char* port ;
string h , p ;
Server* ptr;
//int port_num = 4040;



void client_thread(int req , int  image_id  ,string toConnectIp ,string toConnectPort, int num_views) {

    port = toConnectPort.c_str() ;
    hostname = toConnectIp.c_str();


    Client * c = new Client(hostname, port); //always run on local ip
    c->executePrompt( req , image_id , num_views);

}

void  server_thread(std::string serverName, int port_num) {

//    Server* s = new Server("127.0.0.1", "4040"); //needs to connect to client thus gets ip and port from argsv
//        while(1) {
//                s->serveRequest();
//        }
}



Thread::Thread(bool cli , bool first , int req, int image_id  ,  bool parent, int port_num,  string toConnectIp ,string toConnectPort, int num_views )
    {
//if parent create server object
    //if child method thread at method
    if (parent)
    {
        port_num = 5050;
        ptr = new Server("10.40.44.204",to_string(port_num).c_str()); //needs to connect to client thus gets ip and port from argsv
        //db = ptr->

    }
    if (first) {
        std::thread t1(&Server::serveRequest,ptr);
        t1.detach();
    }


if (cli) {
    std::thread t1(client_thread,  req, image_id   , toConnectIp , toConnectPort,num_views);
    t1.join();
   }
}
