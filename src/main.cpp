#include<iostream>
#include <string>

#include "Message.h"
#include "Client.h"
#include "Server.h"

using namespace std;

void testClient(char **argv){
    Client *client = new Client(argv[1], argv[2]);
}

void testServer(char **argv){
    Server *server = new Server(argv[1], argv[2]);

}
void testMsg(){
    char h[] = "Hello World";
    
    Message m = Message(h, sizeof(h));
    MessageType msg_type = Reply;

    m.setMessageType(msg_type);

    cout << "Original Message: "<< std::endl <<  m;

    // Marshall: Base64 Encode
    char * marshalled = m.marshal();
    cout <<  "Marshalled: " <<  (char *) marshalled << endl;

    // UnMarshall: Base64 Decode
    Message m2 = Message(marshalled);
    cout << "Unmarshalled Message: "<< std::endl <<  m2;

}

int main(int argc,char **argv){
    testServer(argv);
    return 0;
}

