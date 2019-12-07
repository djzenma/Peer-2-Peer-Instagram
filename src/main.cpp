//#include<iostream>


#include <string>
#include "../headers/Peer.h"
#include "../headers/Message.h"

using namespace std;

int main(int argc,char **argv){
   
    // std::string path = (std::string)PATH + "/images/mine/" + std::to_string(4)+ ".jpg";
    // std::string temp_path = (std::string)PATH  + "/images/stego/" + std::to_string(4)+ "_stego.jpg";

    // std::string hidden_text = "Hello";

    // std::string stego_image = stega_encode(path, hidden_text, temp_path);
    // std::string text = stega_decode(temp_path);


    if(strcmp(argv[1], "Server")==0){
        Peer p("10.40.57.51", "Manar", "127.0.0.1");
        p.serveRequst();
    } else {
        Peer p("127.0.0.1", "Manar", "127.0.0.1");
        Message imgMsg;
        p.requestImageFromPeer(imgMsg,4, "10.40.57.51");
    }

    return 0;
}
