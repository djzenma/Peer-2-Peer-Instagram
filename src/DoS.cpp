
#include <iostream>
#include <cmath>
#include <utility>
#include "../headers/DoS.h"
#include "../headers/Database.h"
#include "../headers/Image.h"

#define PHOTOS "photos/"

DoS::DoS(const char *dosIp) {
    this->dosIp = dosIp;
    //com = new Communication();
    //com->authTx = com->init_socket(dosIp, AUTH_PORT);
    //com->loginTx = com->init_socket(dosIp, LOGIN_PORT);
    //com->dbTx = com->init_socket(dosIp, DB_PORT);

    reqRep = new RequestReply(dosIp, AUTH_PORT);
}


/*
 * Listen For Login Requests
 */
#pragma clang diagnostic push // Ignore Infinite Loop
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void DoS::runLoginSys() {
    int new_socket;
    char req[2000] = {0};
    Profile credentials;
    std::map<std::string, std::string>::iterator it;
    char *res;
    sockaddr_in peerAddress;

    std::cout<<"DoS: Listening for Login\n";
    while(true) {

        login_socket = com->listenTx(com->loginTx, req);
        std::cout<<"DoS: Login request= "<<req<<"\n";
        credentials = getCredentials(req);

        try {
            DoS::db.at(credentials.user);
            res = const_cast<char *>("ok");
        } catch (std::out_of_range& exception) {
            res = const_cast<char *>("refused");
        }

        send(login_socket , res , strlen(res) , 0);
        std::cout<<"DoS: sent: "<<res<<"\n";
    }
}
#pragma clang diagnostic pop



/*
 * Listen For Authentication Requests. Steps:
 * 1. Peer Authenticates
 * 2. Peer sends all his photos
 * 3. Peer requests number of samples, DoS sends them
 */
#pragma clang diagnostic push   // Ignore Infinite Loop
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void DoS::runAuthSys() {
    Profile credentials;

    std::cout<<"DoS: Listening for Auth...\n";
    while(true) {
        Message reqMsg = Message();

        // Listening For Authentication
        if(reqRep->recRequest(reqMsg) > 0) {  // Listens for request
            int reqOperation = reqMsg.getOperation();
            std::string ip = std::string(reqMsg.getIP());
            const char *peerIp = ip.c_str();
            std::cout<<"DoS: Peer IP: "<<peerIp<<"\n";

            Message okMsg = buildReplyMsg(reqMsg.getRequestId(), "ok", OK, peerIp, PEER_DEFAULT_PORT);
            switch(reqOperation) {
                case AUTH: {          // 1. Authentication request
                    // Got request
                    std::cout << "DoS: Auth request= " << reqMsg.getMessage() << "\n";
                    credentials = getCredentials(reqMsg.getMessage());

                    // Add peer credentials to db
                    insertInDB(credentials, peerIp);

                    // Send ok Response
                    reqRep->sendMessage(okMsg, peerIp, PEER_DEFAULT_PORT);
                    break;
                }
                case PROFILE: {       // 2. Peer Sends all his photos, req = number of photos
                    // Send ok Response (ok send me your photos)
                    //reqRep->sendMessage(okMsg, peerIp, PEER_DEFAULT_PORT);

                    //int numImgs;
                    //getCredentials_And_NumImgs(credentials, numImgs, reqMsg.getMessage());
                    // Receive his photos
                    std::cout<<"DoS: Received Peer's Images...\n";
                    Profile profile = getAllImages(reqMsg);

                    // Insert him to the Active users List and save his IP
                    activeUsers.insert({profile.user, peerIp});
                    std::cout << "DoS: User " << profile.user<< " added to the active list.\n";
                    break;
                }
                /*
                case SAMPLES_NUM:{  // 3. Send peer number of samples to be sent, then send them
                    std::cout << "DoS: Sending number of samples...\n";
                    int n = 3;  // TODO
                    Message samplesNumMsg = buildReplyMsg(reqMsg.getRequestId(), std::to_string(n), SAMPLES_NUM, peerIp, PEER_DEFAULT_PORT);
                    reqRep->sendMessage(samplesNumMsg, peerIp, PEER_DEFAULT_PORT);
                    break;
                }
                 */
                case SAMPLES: {       // 4. Send peer the samples
                    // Send him All Samples
                    std::cout << "DoS: Sending Samples to IP: " << peerIp << "\n";
                    sendSamples(peerIp, reqMsg.getMessage());
                    break;
                }
                default: break;
            }
        }
    }
}
#pragma clang diagnostic pop



/*
 * The following are Images Helper functions
 */
// Returns Username of the sender
Profile DoS::getAllImages(Message profile) {
    //while(1) {
    //    if(reqRep->recRequest(images) > 0)
    //        break;
    //}
    return Image::reconstructSamplesMsg(true, profile, "");
    //com->getImage(flag ,image, AUTH_PORT, dosIp, PHOTOS);
    //std::cout<<"DoS: Peer Images Received!\n";
}


void DoS::sendSamples(std::string owner_ip, std::string owner_name) {
    std::cout<<"DoS: Sending Samples to the Peer...\n";
    int n = 3;
    int imagesId[3] = {0,1,2};
    Message samples = Image::buildSamplesMsg(true, SAMPLES, imagesId, dosIp, AUTH_PORT,
                                             std::move(owner_name), n);
    std::string numImgs = std::to_string(n);
    samples.setMessage(samples.getMessage() + std::to_string(n), samples.getMessageSize() + numImgs.size() + 1);
    reqRep->sendMessage(samples, owner_ip.c_str(), PEER_DEFAULT_PORT);
    /*
    for (int i = 0; i < 3; i++) {
        Message msg = Image::buildImageMsg(i, owner_ip, owner_name, AUTH_PORT);
        const char * destIp = owner_ip.c_str();
        reqRep->sendMessage(msg, destIp, PEER_IMAGES_PORT);
    }*/
    std::cout<<"DoS: Samples Sent!\n";
}



Profile DoS::getCredentials(std::string request) {
    std::string delimiter = "/";
    Profile credentials;

    size_t pos = 0;
    std::string token;
    while ((pos = request.find(delimiter)) != std::string::npos) {
        token = request.substr(0, pos);
        credentials.user = token;
        request.erase(0, pos + delimiter.length());
    }
    credentials.pass = request;

    return credentials;
}

void DoS::getCredentials_And_NumImgs(Profile& profile, int& imgs, std::string msg) {
    std::string delimiter = "/";

    size_t pos = 0;
    std::string token;
    int i = 0;
    while ((pos = msg.find(delimiter)) != std::string::npos) {
        token = msg.substr(0, pos);
        if(i == 0)
            profile.user = token;
        else if(i == 1)
            profile.pass = token;
        msg.erase(0, pos + delimiter.length());
    }
    imgs = std::stoi(msg);
}

/*
 * The following are DB Functions
 */
void DoS::insertInDB(Profile credentials, std::string ip) {
    std::string username = credentials.user;
    std::string imagesPath = "./../images/users/";
    std::string path = imagesPath + username;
    std::string jsonPath = path + "/profile.json";

    struct stat info;
    int file_stat = stat(path.c_str(), &info);
    if (file_stat != 0) {
        if (mkdir(path.c_str(),S_IRWXU) != 0)
            std::cout << "Not Able to Create Directory\n";
    }
    else if( info.st_mode & S_IFDIR )
        printf( "%s is a directory\n", path.c_str());
    else
        std::cout << "Error occured when creating directory\n";

    std::ofstream o(jsonPath);
    o << std::setw(4) << "{\n}" << std::endl;

    auto cred_db = new Database(jsonPath);

    std::tuple<std::string, std::string, std::string> userInfo(credentials.user, credentials.pass, ip);
    cred_db->insertUser(userInfo);
}

Profile DoS::retrieveUserDB(std::string hostname) {
    std::vector<std::string> usersDirs = globVector("../images/users/*");

    for ( std::string &user : usersDirs) {
        // Delimit by Slash
        std::string delimiter = "/";
        size_t pos = 0;
        while ((pos = user.find(delimiter)) != std::string::npos) {
            user.substr(0, pos);
            user.erase(0, pos + delimiter.length());
        }
        if (user == hostname) {
            // Read Json of the user
            Json::Value userProfile;
            std::ifstream userJson("../images/users/"+user+"/profile.json", std::ifstream::binary);
            userJson >> userProfile;
            Profile profile;
            profile.user = userProfile[user]["username"].asString();
            profile.pass = userProfile[user]["pass"].asString();
            profile.ip = userProfile[user]["ip"].asString();
            return profile;
        }
    }
}



/*
 * The following are Thread Functions
 */

/*
 * Only runs the Login thread
 */
/*void DoS::runLoginThread() {
    loginThread = std::thread(&DoS::runLoginSys, this);
}*/

/*
 * Only runs the Auth thread
 */
void DoS::runAuthThread() {
    authThread = std::thread(&DoS::runAuthSys, this);
}


/*
 * Only runs the DB thread
 */
void DoS::runDBThread() {
    dbThread = std::thread(&DoS::runAuthSys, this);
}


#pragma clang diagnostic push   // Ignore Infinite Loop
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void DoS::runDBSys() {
    std::cout<<"DoS: Listening for DB requests...\n";
    while(true) {
        Message reqMsg = Message();

        if(reqRep->recRequest(reqMsg) > 0) {  // Listening For DB requests
            std::string ip = reqMsg.getIP();
            const char *robotIp = ip.c_str();
            std::cout<<"DoS: Robot IP: "<<robotIp<<"\n";
            std::cout << "DoS: Sending my DB to the Robot...\n";

            // Send the DB to the Robot
            const char * dbSize = std::to_string(db.size()).c_str();
            Message dbSizeMsg = buildRequestMsg(ROBOT, robotIp, ROBOT_PORT, dbSize);
            reqRep->sendMessage(dbSizeMsg, robotIp, DB_PORT);

            // Send the DB entries
            sleep(1);
            std::map<std::string, std::string>::iterator it;
            for ( it = db.begin(); it != db.end(); it++ ){
                char * ip = const_cast<char *>(it->second.data());
                Message userIp = buildRequestMsg(ROBOT, robotIp,ROBOT_PORT, ip);
                reqRep->sendMessage(userIp, robotIp, DB_PORT);
                sleep(1);
            }
            std::cout << "DoS: Finished sending my DB to the Robot...\n";
        }
    }
}
#pragma clang diagnostic pop

DoS::~DoS() {
    if (loginThread.joinable())
        loginThread.join();
    if (authThread.joinable())
        authThread.join();
}

void DoS::join() {
    authThread.join();
    loginThread.join();
}
