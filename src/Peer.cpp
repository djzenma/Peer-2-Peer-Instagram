#include "../headers/Peer.h"

#define PORT 4040

Peer::Peer(const char *myIp, std::string myName, std::string dosIp) {
    this->myIp = myIp;
    this->myName = myName;
    this->dosIp = dosIp;

    rrp = new RequestReply(myIp, PORT);
    db = new Database(std::string(PATH) + "images/DB.json");

    serveThread = std::thread(&Peer::serveRequst,this);
    serveThread.detach();

}

void Peer::Accept(std::string msg_id){
    rrp->Accept(msg_id);
}
void Peer::Reject(std::string msg_id){
    rrp->Reject(msg_id);
}
std::vector<Message> Peer::getPending(){
    return rrp->getPending();
}


int Peer::requestImageFromPeer(Message & imgMsg, int imgId, const char *destPeerIp) {
    Message m = buildRequestMsg(SendImage, imgId);
    std::string send_res = rrp->sendMessage(m, destPeerIp, PORT);
    std::cout << strcmp(send_res.c_str(), "ok") << std::endl; 
    if(strcmp(send_res.c_str(), "ok") == 0){
        Message reply_msg;
        int reply= 0 ;
       // for (int i=0 ;i< 50 && !reply ;i++)
       while(1 && !reply)
        {
            sleep(1);
            reply = rrp->recReply(reply_msg, m.getRequestId());
        }
        
        if(!reply){
            printf("Timeout! Didn't recieve a reply \n");
            return -1;
        }
        else{
            printf("Saving image \n");
            saveImage(reply_msg.getMessage(), 7);
            //imgMsg = reply_msg;
            return -1;    
        }
    }
    else{
        printf("Failed Sending Image request \n");
        return -1;
    }
}

int Peer::requestProfileFromPeer(const char *destPeerIp) {
    Message m = buildRequestMsg(SendProfile, 0);
    std::string send_res = rrp->sendMessage(m, destPeerIp, PORT);
    std::cout << strcmp(send_res.c_str(), "ok") << std::endl;
    if (strcmp(send_res.c_str(), "ok") == 0) {
        Message reply_msg;
        int reply = 0;
        // for (int i=0 ;i< 50 && !reply ;i++)
        while (1 && !reply) {
            sleep(1);
            reply = rrp->recReply(reply_msg, m.getRequestId());
        }

        if (!reply) {
            printf("Timeout! Didn't recieve a reply \n");
            return -1;
        } else {
            printf("Saving image \n");
            saveImage(reply_msg.getMessage(), 7);
            //imgMsg = reply_msg;
            return -1;
        }
    } else {
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
    int sender_port =  msg.getPort();


    std::string username="Manar";

    switch (msg.getOperation())
    {
        case SendImage: { // someone is requesting an image from me.
            int image_id = msg.getImageId();
            int num_views = rand()%10+1;
            Message msg = Image::buildImageMsg(image_id , std::to_string(num_views)+","+username+","+sender_ip, request_id);
            msg.setIP(myIp);
            msg.setPort(PORT);
            rrp->sendMessage(msg, sender_ip.c_str(), sender_port);
            std::tuple<std::string, int> userInfo(username, num_views); //add to db
            db->insertUser(image_id, userInfo);
            break;
        }
        case UpdateViewCount:{ // updates view count for image I owe when someone views it
            int num_views = atoi(msg.getMessage().c_str());
            updateCountFor(image_id, num_views, sender_ip.c_str());
            break;
        }
        case SendProfile:{
            Message msg = Image::buildProfileMsg(request_id);
            msg.setIP(myIp);
            msg.setPort(PORT);
            rrp->sendMessage(msg, sender_ip.c_str(), sender_port);
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
            std::cout << "Handling Accepted msg: " << msg.getRequestId() << std::endl;
            msgIdThread = std::thread(&Peer::dispatch, this, msg);
            msgIdThread.detach();
        }
    }
}


void Peer::join() {
    serveThread.join();
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
            .port=PORT,
            .msg_type = Request
    };

    Message msg = Message(reqinfo);
    return msg;
}

Peer::~Peer(){
   delete rrp;
   delete db;
}