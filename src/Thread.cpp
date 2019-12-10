#include <thread>
#include "../headers/Thread.h"
#include "../headers/Server.h"


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
    /*
    Server* s = new Server("127.0.0.1",to_string(port_num).c_str()); //needs to connect to client thus gets ip and port from argsv
    std::cout<<"Crystal 1"<<endl;
    std::cout<<"port"<<port_num<<endl;
    port_num = port_num+100;
    std::cout<<port_num<<endl;
    /*if (parent){
        std::cout<<"entered          "<<endl;
        int reqNum = -1 ;
        string serverName;
        int image_id;
        Thread * thrd = new Thread(false , true ,  reqNum ,image_id,  serverName,false); //server thread
    }
    else{
        Server* q = new Server("127.0.0.1", "6040");
    //while(1) {
            s->serveRequest(serverName); */
    //}
    //auto f1 = std::async(Server::serveRequest, serverName);

    // s->thread_server(parent);
}



Thread::Thread(bool cli , bool first , int req, int image_id  ,  bool parent, int port_num,  string toConnectIp ,string toConnectPort, int num_views )
    {
//if parent create server object
    //if child method thread at method
    if (parent)
    {
        ptr = new Server("10.40.33.37",to_string(port_num).c_str()); //needs to connect to client thus gets ip and port from argsv

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
