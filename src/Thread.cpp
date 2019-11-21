#include <thread>
#include "../headers/Thread.h"


const char* hostname ;
const char* port ;
string h , p ;

void client_thread(int req , int  image_id , string serverName) {
    cout <<"Who do You want to Connect to (Ip)"; //from Dos
    cin >> h ;
    cout <<"Who do You want to Connect to (Port)"; //from Dos
    cin >> p ;

    port = p.c_str() ;
    hostname = h.c_str();

    Client * c = new Client(hostname, port); //always run on local ip
    c->executePrompt( req , image_id , serverName);

}

void  server_thread() {
    Server* s = new Server("127.0.0.1", "4040"); //needs to connect to client thus gets ip and port from argsv
    while(1) {
            s->serveRequest();
    }
}



 Thread::Thread(bool cli , bool first , int req, int image_id  , string serverName)
{
if (first) {

    std::thread t1(server_thread);
    t1.detach();
}

if (cli) {
    std::thread t1(client_thread,  req, image_id  , serverName);
    t1.join();
   }


}