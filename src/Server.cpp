#include "../headers/Server.h"

#define PATH "/mnt/d/college/Semester 12-- Fall 2019/CSCE 4411 - Fund of Dist Sys/project/Distributed-Client-master (16)/Distributed-Client-master/"
Server::Server(const char * hostname, const char * port){
    std::string path = (std::string)PATH+"server_db.txt";
    this->port = port ;
    this->hostname = hostname ;
    std::string serverIp = hostname_to_ip((char *)hostname);
    //db = new Database(path);
    reqReply = new RequestReply(port, serverIp.c_str(), false, 1024);
    myName = "Bassant";
}
/*
    constructs image msg given an image id
*/
Message buildImageMsg(int image_id ,string hidden, std::string request_id){
    std::string path = "./images/mine/" + to_string(image_id)+ ".jpg";
    std::string temp_path = "./images/stego/" + to_string(image_id)+ "_stego.jpg";
    // get hidden text from DB
    std::string hidden_text = hidden;

    std::string stego_image = stega_encode(path, hidden_text, temp_path);
    std::cout << stego_image ;
    
    requestInfo reqinfo ={.image_id=image_id,
                .request_id= request_id,
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
    std::string request_id = msg.getRequestId();

    std::string username;
    switch (msg.getOperation()){
        case SendImage: { // an image with a specified id
            int image_id = msg.getImageId();
            Message m = buildImageMsg(image_id ,  to_string(rand()%10+1)+","+myName+","+hostname, request_id);
            reqReply->sendReply(m);
            break;
        }
        case SendSample :{ // send three samples
            for(int i=0; i<3; i++){
                Message msg = buildImageMsg(i , myName+","+hostname, request_id);
                reqReply->sendReply(msg);
                sleep(5);
            }
            break;
        }
        case SendImages: { // an image with a specified id
        int no_views = 5; //default
            for(int i=0; i<6; i++){
                Message msg = buildImageMsg(i , myName+","+hostname, request_id);

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
void Server::dec_count(Message m){

}
int Server::serveRequest(){
    Message msg = Message();
    reqReply->getReq(msg);
    printf("Data Recievedx:%s \n", msg.getMessage().c_str()); // msg received
    
    if(msg.getMessageType() == Request) // check that msg is indeed a request message
        dispatch(msg);
    else printf("Server recieved a non request message. \n");

    return 1;
}

Server::~Server(){
    reqReply->shutDownFD();
}
