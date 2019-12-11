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


std::map<std::string, int> Peer::getImageInfo(int img_id) {
    return db->getAllUsers(img_id);
}

int Peer::requestImageFromPeer(int imgId, const char *destPeerIp) {
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
            Image::saveImage(reply_msg.getMessage(),imgId, "requested");
            return -1;
        }
    }
    else{
        printf("Failed Sending Image request \n");
        return -1;
    }
}

// Should take user name as an argument
int Peer::viewImage(int image_id, std::string & path) {
    std::string stego_image = "../images/requested/" + std::to_string(image_id) + ".jpg";
    std::string hidden_text = stega_decode(stego_image, true);
    std::vector<std::string> parsed = parseHidden(hidden_text);

    int num_views = atoi(parsed[0].c_str());
    std::string owner_ip = parsed[1];
    std::string owner_name = parsed[2];

    if (num_views > 0){
        num_views--;
        std::string new_hidden_text = std::to_string(num_views) + hidden_text.substr(hidden_text.find(','));
        stega_encode(std::string(EXTRACTED_IMAGE_PATH), new_hidden_text, stego_image, true);
        path = std::string(EXTRACTED_IMAGE_PATH);

        Message msg = buildRequestMsg(UpdateViewCount, image_id);
        msg.setMessage(std::to_string(num_views),std::to_string(num_views).length());
        msg.setIP(myIp);
        msg.setPort(PORT);

        rrp->sendMessage(msg, owner_ip.c_str(), PORT);
        // Inform Owner of the new count
        return num_views;
    }
    else {
        if( std::remove( std::string(EXTRACTED_IMAGE_PATH).c_str()) != 0 )
            perror( "Error deleting extracted image file" );
        else
            printf( "Extracted image file successfully deleted" );

        if( std::remove(stego_image.c_str()) != 0 )
            perror( "Error deleting  image file" );
        else
            printf( "image file successfully deleted" );
        return num_views;
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
            std::string profile = reply_msg.getMessage();
            Image::reconstructSamplesMsg(reply_msg, "requested/profile" ,6);
            //imgMsg = reply_msg;
            return -1;
        }
    } else {
        printf("Failed Sending Profile request \n");
        return -1;
    }
}


void Peer::updateViewsForPeer(int image_id, int new_count, std::string user_name, const char * peerIp){
    Message msg = buildRequestMsg(UpdateViewsRequestedImage, image_id);
    std::string num_views = std::to_string(new_count);
    msg.setMessage(num_views, num_views.length());
    msg.setIP(myIp);
    msg.setPort(PORT);
    msg.setSenderName(myName);
    rrp->sendMessage(msg, peerIp, PORT);

    db->updateCount(image_id, user_name, new_count);
}
/*
    Updates count for a certain user.
    When the user views an image or when I want to change count;
*/
void Peer::requestMoreViews(int image_id,  const char * peerIp){

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
            int num_views = 2;//rand()%10+1;
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
            db->updateCount(msg.getImageId(), msg.getIP(), num_views);
            break;
        }
        case SendProfile:{
            Message msg = Image::buildProfileMsg(request_id);
            msg.setIP(myIp);
            msg.setPort(PORT);
            rrp->sendMessage(msg, sender_ip.c_str(), sender_port);
        }
        case UpdateViewsRequestedImage:{  // update views for image I requested
            std::string stego_image = "../images/requested/" + std::to_string(msg.getImageId()) + ".jpg";
            std::string hidden_text = stega_decode(stego_image, true);
            std::vector<std::string> parsed = parseHidden(hidden_text);

            int num_views = atoi(parsed[0].c_str());
            std::string owner_ip = parsed[1];
            std::string owner_name = parsed[2];
            std::string new_hidden_text = std::to_string(num_views) + hidden_text.substr(hidden_text.find(','));
            stega_encode(std::string(EXTRACTED_IMAGE_PATH), new_hidden_text, stego_image, true);
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
            .sender_name=myName,
            .msg_type = Request
    };

    Message msg = Message(reqinfo);
    return msg;
}

Peer::~Peer(){
   delete rrp;
   delete db;
}