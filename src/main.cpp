#include <string>
#include <ostream>
#include <fstream>

#include "../headers/Peer.h"
#include "../headers/Message.h"

using namespace std;

int main(int argc,char **argv){
    int n= 0;
    if(strcmp(argv[1], "Server")==0){
        Peer p("10.40.32.170", "Manar", "127.0.0.1");
        sleep(6);

        p.updateViewsForPeer(4,0, "Bassant", "10.40.56.37" );
        sleep(10);

        std::vector<Message> pending = p.getPending();
        for (int i=0; i< pending.size(); i++){
            cout << "Rejecting request: " << pending[i].getRequestId() << std::endl;
            n= n+1;
            p.Accept(pending[i].getRequestId());
        }
        while(true){

        }
    } else {
        Peer p("10.40.32.170", "Manar", "127.0.0.1");
        Message imgMsg;
        p.requestImageFromPeer( 4, "10.40.56.37");
        // sleep(10);
        // p.requestImageFromPeer(imgMsg, 4, "10.7.126.165");
    }

    return 0;
}
