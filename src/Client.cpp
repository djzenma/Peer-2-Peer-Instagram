#include "../headers/Client.h"
#define PATH "/mnt/d/college/Semester 12-- Fall 2019/CSCE 4411 - Fund of Dist Sys/project/Distributed-Client-master (16)/Distributed-Client-master/"
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
    //std::string path = (std::string)PATH+"client_db.txt";
    buffer = new char [buff_size];
    this->port = listen_port ;
    this->hostname = listen_hostname ;
    std::string serverIp = hostname_to_ip((char *)listen_hostname);
    //db = new Database(path);
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
std::string saveImage(std::string image, int image_id){
    std::string temp_loc = (std::string)PATH+"images/requested/" + to_string(image_id) + ".jpg";
    std::ofstream outFile;
    outFile.open(temp_loc);
    outFile << image;
    outFile.close();
    std::string secret_text = stega_decode(temp_loc);
    return secret_text;
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
                if (req_status >= 0){
                    Message reply_msg = Message();
                    if(reqReply->getReply(reply_msg) >= 0)
                        saveImage(reply_msg.getMessage(), reply_msg.getImageId());
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
                    saveImage(reply_msg.getMessage(), reply_msg.getImageId());

                    /*std::vector<std::string> result;
                    std::istringstream iss(s);
                    for(std::string s; iss >> s; )
                        result.push_back(s);
                    /*for (std::vector<std::string>::const_iterator i = result.begin(); i != result.end(); ++i)
                        std::cout << *i << endl;
                    int r = std::atoi(result[1].c_str());
                    std::tuple<std::string, int> t((""+result[3]+result[4]),r);
                    //db->insertUser(image_id,t);
                    */
                }
            }
            break ;
        }
    case 3: //update views when viewing image
    {

        int image_id;
        cout << "Which Picture would you like to view ? ";
        cin >> image_id;

        std::string path = (std::string)PATH+"images/requested/" + to_string(image_id)+ ".jpg";
        std::string temp_path = (std::string)PATH+"images/stego/" + to_string(image_id)+ ".jpg";
        std::string s = stega_decode(path);
        std::cout<<s<<endl;

        std::vector<std::string> result; //parsing string
        std::istringstream iss(s);
        for(std::string s; iss >> s; )
            result.push_back(s);
         if (result[1]== "0")
             printf("error cannot access photo");
         else
            {     result[1] =to_string(atoi(result[1].c_str()) -1);
         std::string new_s = "";
         for (std::vector<std::string>::const_iterator i = result.begin(); i != result.end(); ++i)
                                 new_s += ((std::string)*i + " ");
         std::cout<<new_s<<endl;
         std::string stego_image = stega_encode(path, new_s, temp_path);
         saveImage(stego_image, image_id);

        //send to server
        Message msg = buildRequestMsg(DecrementView,image_id);
        msg.setMessage (result[1], result[1].length());
        int req_status = reqReply->sendReq(msg);
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


Client::~Client(){
     reqReply->shutDownFD();
}
