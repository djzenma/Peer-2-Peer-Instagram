

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

    std::string path = (std::string)PATH +"./../images/DB.json";
    db = new Database(path);

    reqRep = new RequestReply(myIp, PEER_DEFAULT_PORT);
    //reqRep = new RequestReply(myIp, PEER_IMAGES_PORT);
    //reqRep = new RequestReply(myIp, PEER_IMAGES_PORT);

    //com->msgIdTx = com->init_socket(myIp, PEER_IMAGES_ID_PORT);
    runMsgIdThread();
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
        //Message replyMsgNumSamples = sendMsg(SAMPLES_NUM, dosIp_char, AUTH_PORT, "", reqRep, PEER_DEFAULT_PORT, SEND_RECEIVE);

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

    char* cred_char = const_cast<char *>(cred.c_str());
    const char* dosIp_char = dosIp.c_str();

    Message replyMsgChred = sendMsg(LOGIN, dosIp_char, LOGIN_PORT, cred_char, reqRep, PEER_DEFAULT_PORT, SEND_RECEIVE);
    if(replyMsgChred.getOperation() == OK) {
        //std::thread sendImagesThread = std::thread(&Peer::sendMyImgs, this);
        sendMyProfile(true, "", LOGIN_PORT);

        // Request number of Samples
        Message replyMsgNumSamples = sendMsg(SAMPLES_NUM, dosIp_char, LOGIN_PORT, "", reqRep, PEER_DEFAULT_PORT, SEND_RECEIVE);


        // Get The Samples
        // Request number of Samples
        Message replyMsgSamples = sendMsg(SAMPLES, dosIp_char, LOGIN_PORT, myName, reqRep, PEER_DEFAULT_PORT, SEND);

        getSamplesFromDoS();
        return "ok";
    }
    return "refused";
}

void Peer::sendMyProfile(bool toDoS, std::string destIp, int PORT) {
    int n = 3;
    const char* dosIp_char = dosIp.c_str();
    int imagesId[3] = {0,1,2};
    Message samples = Image::buildSamplesMsg(false, PROFILE, imagesId, myIp, PEER_DEFAULT_PORT, myName, n);
    std::string numImgs = std::to_string(n);
    samples.setMessage(samples.getMessage() + std::to_string(n), samples.getMessageSize() + numImgs.size() + 1);

    //Message dosReply = sendMsg(PROFILE, dosIp_char, AUTH_PORT, std::to_string(n), reqRep, PEER_DEFAULT_PORT, SEND_RECEIVE);
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

void Peer::requestProfileFrom(std::string destIp, bool robot) {
    int n = 6;
    const char* destIp_char = destIp.c_str();
    int port;
    if(robot)
        port = ROBOT_PORT;
    else
        port = PEER_IMAGES_ID_PORT;

    RequestReply* rrp = new RequestReply(myIp.c_str(), port);
    Message res = sendMsg(PROFILE, destIp_char, PEER_IMAGES_ID_PORT, "", rrp, PEER_DEFAULT_PORT, SEND_RECEIVE);
    if(res.getMessage() == "ok") {
        for(int i=0; i<n; i++) {
            Message img = receiveMsg(port); // TODO:: Port: PEER_IMAGES_ID_PORT, destination dir: (robot) ? ROBOT+destIp+"/":REQ
            sleep(1);
        }
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


void Peer::sendImageToPeer(Message &m ,std::string destIp, int destPort ) {

    int num_views = rand()%10+1;
    std::tuple<std::string, int> userInfo(destIp, num_views); //add to db
    db->insertUser(m.getImageId(), userInfo);

    const char * destIp_char = destIp.c_str();
    sendMsg(PROFILE, destIp_char, destPort, m.getMessage(), reqRep, PEER_DEFAULT_PORT, SEND);
}

/*
 * Requests an image from a Peer
 */
Message Peer::requestImageFromPeer(int imgId, const char *destPeerIp) {
    bool flag = true ;
    std::cout<<"Peer "<<myName<<": requesting image from other Peer!\n";

    Message res = sendMsg(PROFILE, destPeerIp, PEER_IMAGES_ID_PORT,
                          const_cast<char *>(std::to_string(imgId).c_str()), reqRep, PEER_DEFAULT_PORT, SEND_RECEIVE);
    if(res.getMessage() == "ok") {
        std::cout<<"Peer "<<myName<<": waiting for the image from other Peer!\n";
        Message image;

        receiveMsg(PEER_IMAGES_PORT); // TODO:: PEER_IMAGES_PORT, SAVE PATH = REQ
        std::cout<<"Peer "<<myName<<": Image Received Successfully from other Peer!\n";
        return image;
    }
    else
        std::cout<<"Peer: Image not received from other Peer!\n";
}


std::string Peer::getMyIP() {
    return myIp;
}


std::string Peer::getMyName() {
    return myName;
}
/*
 * Run the Msg Id thread
 */
void Peer::runMsgIdThread() {
    msgIdThread = std::thread(&Peer::runMsgIdSys, this);
}

/*
 * Listens for Msg Id requests
 */
#pragma clang diagnostic push   // Ignore Infinite Loop
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void Peer::runMsgIdSys() {
    int new_socket;

    std::cout<<"Peer: Listening for Msg ID requests...\n";
    while(true) {
        char req[2000] = {0};

        // Listening For Msg ID requests
        //new_socket = com->listenTx(com->msgIdTx, req);
        send(new_socket , "ok" , strlen("ok") , 0);

        if(strcmp(req, "profile") == 0) {
            //std::string peerIp = getIP(com->msgIdTx.address);
            //std::cout << "Peer: Sending My Profile to IP: " << peerIp << "\n";
            //sendMyProfile(false, peerIp, PEER_IMAGES_ID_PORT);
        }
        else {
            // Send him the requested ID
            //std::string peerIp = getIP(com->msgIdTx.address);
            //std::cout << "Peer: Sending The requested image with ID "<<req<<" to IP: " << peerIp << "\n";
            //Message imgMsg = com->buildImageMsg(std::stoi(req), myIp, myName);
            //sendImageToPeer(imgMsg,peerIp, PEER_IMAGES_PORT ) ;
            //std::cout << "Peer "<<myName<<": Finished Sending The requested image with ID "<<req<<" to IP: " << peerIp << "\n";
        }

    }
}

#pragma clang diagnostic pop

void Peer::join() {
if (msgIdThread.joinable())
msgIdThread.join();
}

std::vector<Message> Peer::getDbFromDoS(int n) {
    std::vector<Message> images;
    bool flag = true ;
    for (int i=0; i<n; i++) {
        Message image;
        // com->getImage(flag ,image, PEER_IMAGES_PORT, myIp, );
        images.push_back(image);
    }
    return images;
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void Peer::listenForDBRequests (const char *destIp  )
{
    int new_socket;
    std::cout<<"Peer: Listening for DB requests...\n";
    while(true) {
        char req[2000] = {0};

        // Listening For DB requests
        //new_socket = com->listenTx(com->peerDBTx, req);
        //std::string robotIp = getIP(com->peerDBTx.address);
        //std::cout<<"Peer: Robot IP: "<<robotIp<<"\n";

        if(strcmp(req, "robot") == 0) {   // Send the DB to the Robot
            std::cout << "Peer: Sending my DB to the Robot...\n";

            //what if image not sent to any one
            int numImages = 6 ;
            for (int i=0 ; i< numImages ;i++) { //loop over images
                std::map <std::string,int> table= db->getAllUsers(i);
                int mapSize = table.size();
                const char * dbSize = std::to_string(mapSize).c_str(); //listen foe size*2
                send(new_socket, dbSize, strlen(dbSize), 0);

                std::map<std::string, int>::iterator it;
                for ( it = table.begin(); it != table.end(); it++ )
                {
                    //com->comMsg(destIp, DB_PORT, const_cast<char *>(it->first.c_str()), SEND);
                    sleep(1);
                    //com->comMsg(destIp, DB_PORT, const_cast<char *>(std::to_string(it->second).c_str()), SEND);
                    sleep(1);
                }

            }

            std::cout << "Peer: Finished sending my DB to the Robot...\n";
        }
    }

}
#pragma clang diagnostic pop


void Peer::getDB (const char *destIp )
{
    std::string path = (std::string)PATH +ROBOT +"/"+destIp+".json";
    std::ofstream o(path);
    o << std::setw(4) << "{\n}" << std::endl;

    db = new Database(path);


    int num_images = 6 ;
    std::string robot = "robot";/*
    char* res = com->comMsg(destIp, DB_PORT, const_cast<char *>(robot.c_str()), SEND_RECEIVE); //send request
    if(strcmp(res,"ok") == 0) {
       for (int i=0 ;i<num_images ;i++ ) { //for ever image
           char *dbSize = com->comMsg(const_cast<char *>(myIp.c_str()), DB_PORT, "", RECEIVE); // get size of image db
           for (int j =0 ; j < std::stoi(dbSize) ; j++) //for every peer with that image
           {

               //char *ip = com->comMsg(const_cast<char *>(myIp.c_str()), DB_PORT, "", RECEIVE); // get size of image db
               char *numViews = com->comMsg(const_cast<char *>(myIp.c_str()), DB_PORT, "", RECEIVE); // get size of image db

               std::tuple<std::string, int> userInfo(ip, std::stoi(numViews));
               db->insertUser(i, userInfo);
           }
       }
    }

    else
        std::cout<<"Peer: Image not received from other Peer!\n";*/

}

