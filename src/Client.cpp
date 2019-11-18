#include "../headers/Client.h"
#include <iostream>
using namespace std ;

enum serviceOperations{
    SendImage = 0,
    GrantAccess = 1,
    DecrementView = 2,
    SendSample = 3,
    SendImages = 4
};


Client::Client(const char * listen_hostname, const char * listen_port){
    buffer = new char [buff_size];
    this->port = listen_port ;
    this->hostname = listen_hostname ;
    std::string serverIp = hostname_to_ip((char *)listen_hostname);
    reqReply = new RequestReply(listen_port,  serverIp.c_str(), true, 1024);
}
Message buildRequestMsg(serviceOperations operation, int image_id ){
    requestInfo reqinfo ={.image_id=image_id,
            .storage_location="",
            .p_message= "",
            .operation = operation,
            .rpc_id = 5,
            .msg_type = Request };
    Message msg = Message(reqinfo);
    return msg;
}
string saveImage(std::string image, int image_id){
    std::string temp_loc = "/Users/owner/CLionProjects/Distributed-Client/images/requested/" + to_string(image_id) + ".jpg";
    std::ofstream outFile;
    outFile.open(temp_loc);
    outFile << image;
    outFile.close();
    std::string secret_text = stega_decode(temp_loc);
    return secret_text ;
}
void Client::executePrompt() {
    cout << "Enter Request Number" ;
    cin >> req;
    switch (req) {

        case 0: // request samples from a specific user
        {
            cout << "Enter User Requested ";
            cin >> name;
            // before get host ip and port
            for (int i=0; i<3; i++){
                Message m = buildRequestMsg(SendSample, i);
                int req_status = reqReply->sendReq(m); 
                if (req_status >= 0) {
                    Message reply_msg = Message();
                    if (reqReply->getReply(reply_msg) >= 0) {
                    saveImage(reply_msg.getMessage(), reply_msg.getImageId());
                }
                }
            }
            break;
        }
        case 1:{ //All photos
            cout << "Enter User Requested ";
            cin >> name;
            // before get host ip and port
            for (int i=0; i<6; i++){
                Message m = buildRequestMsg(SendImages, i);
                int req_status = reqReply->sendReq(m);
                if (req_status >= 0){
                    Message reply_msg = Message();
                    if(reqReply->getReply(reply_msg) >= 0)
                        saveImage(reply_msg.getMessage(), reply_msg.getImageId());
                }
            }
            break;
        }
        case 2: //send 1 photo
        {   
            int image_id;
            cout << "Which Picture would you like to view ? ";
            cin >> image_id;

            Message msg = buildRequestMsg(SendImage, image_id);
            int req_status = reqReply->sendReq(msg); 

            if (req_status >= 0){
                Message reply_msg = Message();
                if(reqReply->getReply(reply_msg) >= 0){
                    hiddenText =  saveImage(reply_msg.getMessage(), reply_msg.getImageId());
                    stringstream ss(hiddenText);
                    string  token [3];
                    int i =0 ;
                    while (getline(ss, token[i], ',')) {
                        i++ ;
                    }
                    numViews = stoi(token[0]);
                    senderName= token[1];
                    senderIp= token[2];}
            }
            break ;
        }
    }
}
int Client::requestNumber(int req) {
    requestInfo reqinfo ={.image_id=1,
                .storage_location="manar",
                .p_message= "",
                .operation = req,
                .rpc_id = 5,
                .msg_type = Reply };

    Message msg = Message(reqinfo);

    printf("\nSending a Request of index: %i\n", req);
    return reqReply->sendReq(msg); //sends request number to server
}

int Client::requestSamples(std::string s ) {
    printf("Receiving Samples ...\n");
    Message m = Message();
    return reqReply->getReply(m) ; // receives photo
    //reqReply->shutDownFD();
}

bool Client::req_photo(int photoid, const char *hostname, const char *port)
{
    int requestStatus, replyStatus;
    List::entry e;
    e.port= (char*)port;
    e.hostname=(char*)hostname;
    e.photoid=photoid;
    int val = 0;
    if(!lookup_table.search(e))  //define search function as well the undefined crap if needed
    {
        lookup_table.insertFirst(e,val);  //could be a table of pic/needs to expand
    }
}

Client::~Client(){
     reqReply->shutDownFD();
}
