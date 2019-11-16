#include "../headers/Client.h"
#include <iostream>
using namespace std ;

enum serviceOperations{
    SendImage = 0,
    GrantAccess = 1,
    DecrementView = 2,
    SendSample = 3,
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
void saveImage(std::string image, int image_id){
    std::string temp_loc = "/Users/owner/CLionProjects/Distributed-Client/images/requested/" + to_string(image_id) + ".jpg";
    std::ofstream outFile;
    outFile.open(temp_loc);
    outFile << image;
    outFile.close();
    std::string secret_text = stega_decode(temp_loc);
}
void Client::executePrompt() {
    cout << "Enter Request Number" ;
    cin >> req;
    switch (req) {
        case 0:{ //Samples
        for (int i=1 ;i<2;i++) {
            std::string s = "/Users/owner/CLionProjects/Distributed-Client/got" + std::to_string(i) + ".jpg";
            if (!requestSamples(s))
                {
                    perror("Error Requesting Samples from Server");
                    int flag = 0;
                    for (int i = 0; i < 3 && flag == 0; i++) {
                        flag = !requestSamples(s);
                    }
                }
        }
        break;
        }
        case 1: // request samples from a specific user
        {
            cout << "Enter User Requested ";
            cin >> name;
            // before get host ip and port
            for (int i=0; i<3; i++){
                Message m = buildRequestMsg(SendSample, i);
                int req_status = reqReply->sendReq(m); 
                if (req_status >= 0){
                    Message reply_msg = Message();
                    if(reqReply->getReply(reply_msg) >= 0)
                        saveImage(reply_msg.getMessage(), reply_msg.getImageId());
                }
            }
            break;
        }
        case 2:
        {   
            int image_id;
            cout << "Which Picture would you like to view ? ";
            cin >> image_id;

            Message msg = buildRequestMsg(SendImage, image_id);
            int req_status = reqReply->sendReq(msg); 

            if (req_status >= 0){
                Message reply_msg = Message();
                if(reqReply->getReply(reply_msg) >= 0){
                    saveImage(reply_msg.getMessage(), reply_msg.getImageId());
                }
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
