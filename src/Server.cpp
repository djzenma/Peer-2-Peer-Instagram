#include "../headers/Server.h"

Server::Server(const char * hostname, const char * port){
    this->port = port ;
    this->hostname = hostname ;
    std::string serverIp = hostname_to_ip((char *)hostname);
    reqReply = new RequestReply(port, serverIp.c_str(), false, 1024);
}
/*
    constructs image msg given an image id
*/
Message buildImageMsg(int image_id){
    std::string path = "/Users/owner/CLionProjects/Distributed-Client//images/mine/" + to_string(image_id)+ ".jpg";
    std::string temp_path = "/Users/owner/CLionProjects/Distributed-Client/images/stego/" + to_string(image_id)+ "_stego.jpg";
    // get hidden text from DB
    std::string hidden_text = "Manar: 3, Aya: 5";
    std::string stego_image = stega_encode(path, hidden_text, temp_path);
    std::cout << stego_image ;
    requestInfo reqinfo ={.image_id=image_id,
                .storage_location="",
                .p_message= stego_image,
                .operation = SendImage,
                .rpc_id = 5,
                .msg_type = Reply };
            
    Message msg = Message(reqinfo);
    std::cout << msg ;
    return msg;
}

void Server::dispatch(Message & msg){
    printf("Request Number: %i\n", msg.getOperation());
    switch (msg.getOperation()){
        case SendImage: { // an image with a specified id
            int image_id = msg.getImageId();
            Message m = buildImageMsg(image_id);
            reqReply->sendReply(m);
            break;
        }
        case SendSample :{ // send three samples
            for(int i=0; i<3; i++){
                Message msg = buildImageMsg(i);
                reqReply->sendReply(msg); 
                sleep(5);
            }
            break;
        }
        case GrantAccess :
            break;
        case DecrementView :
            break;
        default:
            break;
    }
}
void Server::serveRequest(){
    Message msg = Message();
    reqReply->getReq(msg);
    dispatch(msg);
}

Server::~Server(){
    reqReply->shutDownFD();
}