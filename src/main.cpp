#include <string>
#include <ostream>
#include <fstream>

#include "../headers/Peer.h"
#include "../headers/Message.h"

using namespace std;

int main(int argc,char **argv){

    if(strcmp(argv[1], "Server")==0){
        Peer p("10.40.32.170", "Manar", "127.0.0.1");
        p.serveRequst();
    } else {
        Peer p("10.40.32.170", "Manar", "127.0.0.1");
        Message imgMsg;
        p.requestImageFromPeer(imgMsg, 4, "127.0.0.1");
        // sleep(10);
        // p.requestImageFromPeer(imgMsg, 4, "10.7.126.165");
    }

    return 0;
}
