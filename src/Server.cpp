#include "../headers/Server.h"
#include "../headers/Thread.h"
#include <stdlib.h>

#define PATH "/Users/owner/CLionProjects/Distributed-Client/"

Server::Server(const char * hostname, const char * port){
    std::string path = (std::string)PATH+"server_db.txt";
    this->port = port ;
    this->hostname = hostname ;
    std::string serverIp = hostname_to_ip((char *)hostname);
    //db = new Database(path);
    reqReply = new RequestReply(port, serverIp.c_str(), false, 1024);
}
/*
    constructs image msg given an image id
*/
Message buildImageMsg(int image_id ,string hidden){
    std::string path = (std::string)PATH +"images/mine/" +to_string(image_id)+ ".jpg";
    std::string temp_path = (std::string)PATH +"images/stego/"+ to_string(image_id)+ "_stego.jpg";
    // get hidden text from DB
    std::string hidden_text = hidden;

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
    int image_id = msg.getImageId();
    std::string username;
    switch (msg.getOperation()){
        case SendImage: { // an image with a specified id
            int image_id = msg.getImageId();
            Message m = buildImageMsg(image_id ,  to_string(rand()%10+1)+","+(string)port+","+hostname);

            reqReply->sendReply(m);
            break;
        }
        case SendSample :{ // send three samples
            for(int i=0; i<3; i++){
                Message msg = buildImageMsg(i ,(string) port+","+hostname);
                reqReply->sendReply(msg);
                sleep(5);
            }
            break;
        }
        case SendImages: { // an image with a specified id
        int no_views = 5; //default
            for(int i=0; i<6; i++){
                Message msg = buildImageMsg(i , (string)port+","+hostname);

                reqReply->sendReply(msg);
                sleep(5);
                /*//add in db
                std::tuple<std::string, int> t(username,no_views);
                db->insertUser(std::to_string(image_id),t);*/
            }
            break;
        }
        case GrantAccess :
            break;
            /*case DecrementView :{
                //add in db
                string t = msg.getMessage();
                db->updateCount(image_id, username, atoi(t.c_str()));

                    break;
            }
                default:
                    break;
            }*/
}
}

int Server::serveRequest(std::string serverName){
    //else{
        string toConnectIp ;
        string toConnectPort ;
        int r = rand()%((65535 - 4040) + 1) + 4040;
        Message msg = Message();
        reqReply->getReq(msg);
        std::cout<<"entered          "<<endl;
        int reqNum = msg.getMessageType() ;
        int image_id= msg.getImageId();
        Thread * thrd = new Thread(false , true ,  reqNum ,image_id,  serverName, r ,  toConnectIp , toConnectPort); //server thread
        printf("Data Recieved:%s \n", msg.getMessage().c_str()); // msg received

    dispatch(msg);
    //}
    return 1;
}

Server::~Server(){
    reqReply->shutDownFD();
}
