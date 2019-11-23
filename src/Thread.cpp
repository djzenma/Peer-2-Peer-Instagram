#include <thread>
#include "../headers/Thread.h"


const char* hostname ;
const char* port ;
//int port_num = 4040;


void client_thread(int req , int  image_id , string serverName ,string toConnectIp ,string toConnectPort ) {


    port = toConnectPort.c_str() ;
    hostname = toConnectIp.c_str();

    Client * c = new Client(hostname, port); //always run on local ip
    c->executePrompt( req , image_id , serverName);

}

void  server_thread(std::string serverName, int port_num) {
    Server* s = new Server("10.40.37.247",to_string(port_num).c_str()); //needs to connect to client thus gets ip and port from argsv
    std::cout<<"port: "<<port_num<<endl;
    port_num = port_num+100;


            s->serveRequest(serverName);

}



 Thread::Thread(bool cli , bool first , int req, int image_id  , string serverName, int port_num , string toConnectIp ,string toConnectPort )
{
if (first) {

    std::thread t1(server_thread,serverName, port_num);
    t1.detach();
}

if (cli) {
    std::thread t1(client_thread,  req, image_id  , serverName , toConnectIp , toConnectPort);
    t1.join();
   }


}
