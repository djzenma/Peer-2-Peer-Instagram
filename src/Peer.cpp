#include "Peer.h"

Peer::Peer(const char *myIp, std::string myName, std::string dosIp) {
    this->myIp = myIp;
    this->myName = myName;
    this->dosIp = dosIp;

    rrp = new RequestReply(myIp);
    db = new Database(std::string(PATH) + "images/DB.json");
}


int Peer::requestImageFromPeer(Message & imgMsg,int imgId, const char *destPeerIp) {
    Message m = buildRequestMsg(SendImage, imgId);
    std::string send_res = rrp->sendMessage(m, destPeerIp);
    std::cout << strcmp(send_res.c_str(), "ok") << std::endl; 
    if(strcmp(send_res.c_str(), "ok") == 0){
        Message reply_msg;
        //sleep(6);
        while (true)
        {
            rrp->recReply(reply_msg, m.getRequestId());
        }
        
        if(rrp->recReply(reply_msg, m.getRequestId()) == 0){
            printf("Timeout! Didn't recieve a reply \n");
            return -1;
        }
        else{
            imgMsg = reply_msg;
            return -1;    
        }
    }
    else{
        printf("Failed Sending Image request \n");
        return -1;
    }
}


/*
    Updates count for a certain user.
    When the user views an image or when I want to change count;
*/
void Peer::updateCountFor(int image_id, int updated_cout,  const char * peerIp){

}
/*
    Handles all Request Messages.
*/
void Peer::dispatch(Message  msg){

    printf("Request Number: %i\n", msg.getOperation());

    int image_id = msg.getImageId();
    std::string request_id = msg.getRequestId();
    std::string sender_ip = msg.getIP();

    std::string username="Manar";

    switch (msg.getOperation())
    {
        case SendImage: { // someone is requesting an image from me.
            int image_id = msg.getImageId();
            int num_views = rand()%10+1;
            Message msg = Image::buildImageMsg(image_id , std::to_string(num_views)+","+username+","+sender_ip, request_id);
            
            std::string hi = "AA";
            for(int i=0; i<1024; i++){
                 hi = hi + "A";
            }
            hi = hi + "BBBBBBBBBBB";

            msg.setMessage(hi, hi.length()+1);
            rrp->sendMessage(msg, sender_ip.c_str());
            std::tuple<std::string, int> userInfo(username, num_views); //add to db
            db->insertUser(image_id, userInfo);
            break;
        }
        case UpdateViewCount:{ // updates view count for image I owe when someone views it
            int num_views = atoi(msg.getMessage().c_str());
            updateCountFor(image_id, num_views, sender_ip.c_str());
            break;
        }
     
    };
}
/*
    Always listens for request messages.
*/

void Peer::serveRequst(){
    while(true){
        Message msg = Message();
        if(rrp->recRequest(msg) > 0){
            std::cout << "Handling msg: " << msg.getRequestId() << std::endl; 
            msgIdThread = std::thread(&Peer::dispatch, this, msg);
            join();
        }
    }
}

void Peer::join() {
    if (msgIdThread.joinable())
        msgIdThread.join();
}

std::string Peer::getMyIP() {
    return myIp;
}

std::string Peer::getMyName() {
    return myName;
}

std::string generateRequestId(Peer * p){
    static int req_num = 0;
    std::cout << std::string(p->getMyIP()) + std::to_string(req_num) << std::endl;
    return std::string(p->getMyIP()) + std::to_string(req_num++);
}


Message Peer::buildRequestMsg(serviceOperations operation, int image_id ){
    
    requestInfo reqinfo = {
            .image_id=image_id,
            .request_id= generateRequestId(this),
            .p_message= "",
            .operation = operation,
            .packet_index = 0,
            .IP=this->getMyIP(),
            .msg_type = Request
    };

    Message msg = Message(reqinfo);
    return msg;
}

Peer::~Peer(){
   delete rrp;
   delete db;
}