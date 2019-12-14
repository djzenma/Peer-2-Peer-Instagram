

#include "../headers/Peer.h"
#include "../headers/DoS.h"
#include "../headers/utils.h"
#include "../headers/Image.h"

#define PATH "/Users/owner/CLionProjects/Distributed-Client/"
#define REQ  "requested/"
#define SAMPLES_DIR  "samples/"
#define ROBOT  "robot/"



Peer::Peer(const char *myIp, std::string myName, std::string dosIp) {
    this->myIp = myIp;
    this->myName = myName;
    this->dosIp = dosIp;
    //com = new Communication();


    reqRep = new RequestReply(myIp, PEER_DEFAULT_PORT);
    //reqRepAuth = new RequestReply(myIp, PEER_IMAGES_PORT);
    //reqRepAuth = new RequestReply(myIp, PEER_IMAGES_PORT);

    db = new Database("../images/DB.json");

    serveThread = std::thread(&Peer::serveRequst,this);
    serveThread.detach();

}

Message Peer::sendMsg(DOS_OPERATIONS operation, const char *destIp, int destPort, std::string msg,
                      RequestReply *rrp, int listenPort, int SEND_OR_RECEIVE) {
    if(SEND_OR_RECEIVE == SEND_RECEIVE) {
        Message reqMsg = buildRequestMsg(operation, myIp, listenPort, msg);
        rrp->sendMessage(reqMsg, destIp, destPort);

        // Wait for reply
        Message replyMsg;
        int replyStat= 0;
        for (int i=0 ;i< 50 && !replyStat ;i++) {
            replyStat = rrp->recReply(replyMsg, reqMsg.getRequestId());
            sleep(1);
        }

        return replyMsg;
    }
    else if(SEND_OR_RECEIVE == SEND) {
        Message reqMsg = buildRequestMsg(operation, myIp, listenPort, msg);
        rrp->sendMessage(reqMsg, destIp, destPort);
        Message m;
        return m;
    }
}


Message Peer::receiveMsg(const int PORT) {
    RequestReply *rrp = new RequestReply(myIp.c_str(), PORT);
    // Wait for reply
    Message replyMsg;
    int replyStat = 0;
    for (int i = 0; i < 50 && !replyStat; i++) {
        replyStat = rrp->recReply(replyMsg, replyMsg.getRequestId());
        sleep(1);
    }
    return replyMsg;
}

/*
 * 1. Peer Authenticates
 * 2. Peer sends all his photos
 * 3. Peer requests the number of samples that he will receive
 * 4. Peer receives the samples
 */
std::string Peer::authenticate(std::string username, std::string password) {
    std::string cred = username + "/" + password;

    const char* dosIp_char = dosIp.c_str();

    Message replyMsgChred = sendMsg(AUTH, dosIp_char, AUTH_PORT, cred, reqRep, PEER_DEFAULT_PORT, SEND_RECEIVE);
    if(replyMsgChred.getOperation() == OK) {    // If response is ok
        // Send my images
        //std::thread sendImagesThread = std::thread(&Peer::sendMyImgs, this);
        sendMyProfile(true, "", AUTH_PORT);

        // Request number of Samples
        //Message replyMsgNumSamples = sendMsg(SAMPLES_NUM, dosIp_char, AUTH_PORT, "", reqRepAuth, PEER_DEFAULT_PORT, SEND_RECEIVE);

        // Request The Samples
        std::cout<<"Peer: Requesting Samples from DoS...\n";
        Message replyMsgSamples = sendMsg(SAMPLES, dosIp_char, AUTH_PORT, myName, reqRep, PEER_DEFAULT_PORT, SEND);

        getSamplesFromDoS();
        return "ok";
    }
    return "refused";

}


std::string Peer::login(std::string username, std::string password) {
    std::string cred = username + "/" + password;

    const char* dosIp_char = dosIp.c_str();

    Message replyMsgChred = sendMsg(LOGIN, dosIp_char, LOGIN_PORT, cred, reqRep, PEER_DEFAULT_PORT, SEND_RECEIVE);
    if(replyMsgChred.getOperation() == OK) {    // If response is ok
        // Send my images
        sendMyProfile(true, "", LOGIN_PORT);

        // Request The Samples
        std::cout<<"Peer: Requesting Samples from DoS...\n";
        Message replyMsgSamples = sendMsg(SAMPLES, dosIp_char, LOGIN_PORT, myName, reqRep, PEER_DEFAULT_PORT, SEND);

        getSamplesFromDoS();
        return "ok";
    }
    else
        return "refused";
}

void Peer::sendMyProfile(bool toDoS, std::string destIp, int PORT) {
    int n = 3;
    const char* dosIp_char = dosIp.c_str();
    int imagesId[3] = {0,1,2};
    Message samples = Image::buildSamplesMsg(false, PROFILE, imagesId, myIp, PEER_DEFAULT_PORT, myName, n);
    std::string numImgs = std::to_string(n);
    samples.setMessage(samples.getMessage() + std::to_string(n), samples.getMessageSize() + numImgs.size() + 1);

    //Message dosReply = sendMsg(PROFILE, dosIp_char, AUTH_PORT, std::to_string(n), reqRepAuth, PEER_DEFAULT_PORT, SEND_RECEIVE);
    //if(dosReply.getOperation() == OK) {
    // Send my photos
    if(toDoS) {
        std::cout<<"Peer: Sending my images to DoS...\n";
        reqRep->sendMessage(samples, dosIp_char, PORT);   // AUTH PORT
    }
    else {
        std::cout<<"Peer: Sending my images to Peer...\n";
        const char * destIp_char = destIp.c_str();
        reqRep->sendMessage(samples, destIp_char, PORT);    // PEER_IMAGES_ID_PORT
    }
}


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void Peer::getSamplesFromDoS() {
    Message samples;
    while(1) {
        if(reqRep->recRequest(samples) > 0) {
            Image::reconstructSamplesMsg(false, samples, "requested/samples");
            break;
        }
    }
}
#pragma clang diagnostic pop


std::string Peer::getMyIP() {
    return myIp;
}


std::string Peer::getMyName() {
    return myName;
}




void Peer::join() {
    serveThread.join();
}





void Peer::Accept(std::string msg_id){
    reqRep->Accept(msg_id);
}

void Peer::Reject(std::string msg_id){
    reqRep->Reject(msg_id);
}

std::vector<Message> Peer::getPending(){
    return reqRep->getPending();
}


std::map<std::string, int> Peer::getImageInfo(int img_id) {
    return db->getAllUsers(img_id);
}


int Peer::requestImageFromPeer(int imgId, const char *destPeerIp) {
    Message m = buildRequest(SendImage, imgId);
    m.setSenderName(myName);
    std::string send_res = reqRep->sendMessage(m, destPeerIp, PEER_DEFAULT_PORT);
    std::cout << strcmp(send_res.c_str(), "ok") << std::endl;
    if(strcmp(send_res.c_str(), "ok") == 0){
        Message reply_msg;
        int reply= 0 ;
        // for (int i=0 ;i< 50 && !reply ;i++)
        while(1 && !reply)
        {
            sleep(1);
            reply = reqRep->recReply(reply_msg, m.getRequestId());
        }

        if(!reply){
            printf("Timeout! Didn't recieve a reply \n");
            return -1;
        }
        else{
            printf("Saving image \n");
            Image::saveImage(reply_msg.getMessage(),imgId, "requested/images/" + reply_msg.getSenderName()  );
            return -1;
        }
    }
    else{
        printf("Failed Sending Image request \n");
        return -1;
    }
}

// Should take user name as an argument
int Peer::viewImage(int image_id, std::string userName) {
    std::string stego_image = "../images/requested/images/"+userName+"/" + std::to_string(image_id) + ".jpg";
    std::string extracted_path = "../images/stego/temp/" + userName + "_" + std::to_string(image_id) + ".jpg";
    std::string hidden_text = stega_decode(stego_image, extracted_path, true);
    std::vector<std::string> parsed = parseHidden(hidden_text);

    int num_views = atoi(parsed[0].c_str());
    std::string owner_ip = parsed[1];
    std::string owner_name = parsed[2];

    if (num_views > 0){
        num_views--;
        std::string new_hidden_text = std::to_string(num_views) + hidden_text.substr(hidden_text.find(','));
        stega_encode(extracted_path, new_hidden_text, stego_image, true);

        Message msg = buildRequest(UpdateViewCount, image_id);
        msg.setMessage(std::to_string(num_views),std::to_string(num_views).length());
        msg.setIP(myIp);
        msg.setPort(PEER_DEFAULT_PORT);
        msg.setSenderName(myName);

        reqRep->sendMessage(msg, owner_ip.c_str(), PEER_DEFAULT_PORT);
        // Inform Owner of the new count
        return num_views;
    }
    else {
        if( std::remove( extracted_path.c_str()) != 0 )
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
    Message m = buildRequest(SendProfile, 0);
    m.setSenderName(myName);
    std::string send_res = reqRep->sendMessage(m, destPeerIp, PEER_DEFAULT_PORT);
    std::cout << strcmp(send_res.c_str(), "ok") << std::endl;
    if (strcmp(send_res.c_str(), "ok") == 0) {
        Message reply_msg;
        int reply = 0;
        // for (int i=0 ;i< 50 && !reply ;i++)
        while (1 && !reply) {
            sleep(1);
            reply = reqRep->recReply(reply_msg, m.getRequestId());
        }

        if (!reply) {
            printf("Timeout! Didn't recieve a reply \n");
            return -1;
        } else {
            printf("Saving image \n");
            std::string profile = reply_msg.getMessage();
            Image::reconstructSamplesMsg(reply_msg, "requested/profile/"+ reply_msg.getSenderName() ,6);
            //imgMsg = reply_msg;
            return -1;
        }
    } else {
        printf("Failed Sending Profile request \n");
        return -1;
    }
}


void Peer::updateViewsForPeer(int image_id, int new_count, std::string user_name, const char * peerIp){
    Message msg = buildRequest(UpdateViewsRequestedImage, image_id);
    std::string num_views = std::to_string(new_count);
    msg.setMessage(num_views, num_views.length());
    msg.setIP(myIp);
    msg.setPort(PEER_DEFAULT_PORT);
    msg.setSenderName(myName);
    reqRep->sendMessage(msg, peerIp, PEER_DEFAULT_PORT);

    db->updateCount(image_id, user_name, new_count);
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


    std::string username = msg.getSenderName();

    switch (msg.getOperation())
    {
        case SendImage: { // someone is requesting an image from me.
            int image_id = msg.getImageId();
            int num_views = 2;//rand()%10+1;
            Message msg = Image::buildImageMsg(image_id , std::to_string(num_views)+","+myIp +"," +myName +",", request_id);
            msg.setIP(myIp);
            msg.setPort(PEER_DEFAULT_PORT);
            msg.setSenderName(myName);
            reqRep->sendMessage(msg, sender_ip.c_str(), sender_port);
            std::tuple<std::string, int> userInfo(username, num_views); //add to db
            db->insertUser(image_id, userInfo);
            break;
        }
        case UpdateViewCount:{ // updates view count for image I owe when someone views it
            int num_views = atoi(msg.getMessage().c_str());
            db->updateCount(msg.getImageId(), msg.getSenderName(), num_views);
            break;
        }
        case SendProfile:{
            Message msg = Image::buildProfileMsg(request_id);
            msg.setIP(myIp);
            msg.setPort(PEER_DEFAULT_PORT);
            msg.setSenderName(myName);
            reqRep->sendMessage(msg, sender_ip.c_str(), sender_port);
            break ;
        }
        case UpdateViewsRequestedImage:{  // update views for image I requested
            std::string stego_image = "../images/requested/images/" + username + "/" + std::to_string(msg.getImageId()) + ".jpg";
            std::string extracted_path = "../images/stego/temp/" + request_id + ".jpg";
            std::string extracted_text = "../images/stego/temp/" + request_id + ".txt";
            std::string hidden_text = stega_decode(stego_image, extracted_path, true);
            std::string num_views = msg.getMessage();
            std::string new_hidden_text = num_views + hidden_text.substr(hidden_text.find(','));
            stega_encode(extracted_path , new_hidden_text, stego_image, true);
            break;
        }
    };
}

/*
    Always listens for request messages.
*/
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void Peer::serveRequst(){
    while(true){
        Message msg = Message();
        if(reqRep->recRequest(msg) > 0){
            std::cout << "Handling Accepted msg: " << msg.getRequestId() << std::endl;
            serveThread = std::thread(&Peer::dispatch, this, msg);
            serveThread.detach();
        }
    }
}
#pragma clang diagnostic pop

Message Peer::buildRequest(serviceOperations operation, int image_id ){

    requestInfo reqinfo = {
            .image_id=image_id,
            .request_id= generateRequestId(this->myIp),
            .p_message= "",
            .operation = operation,
            .packet_index = 0,
            .IP=this->getMyIP(),
            .port=PEER_DEFAULT_PORT,
            .sender_name=myName,
            .msg_type = Request
    };

    Message msg = Message(reqinfo);
    return msg;
}

Peer::~Peer(){
    delete reqRep;
    delete db;
}