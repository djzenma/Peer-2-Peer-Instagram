#include "../headers/Server.h"
#include "../headers/Thread.h"
#include <stdlib.h>

#define PATH "/Users/owner/CLionProjects/Distributed-Client/"

Server::Server(const char * hostname, const char * port){
    std::string path = std::string(get_current_dir_name())+"/images/DB.json";
    this->port = port ;
    this->hostname = hostname ;
    std::string serverIp = hostname_to_ip((char *)hostname);
    db = new Database(path);
    reqReply = new RequestReply(port, serverIp.c_str(), false, 1024);
}
/*
    constructs image msg given an image id
*/
Message buildImageMsg(int image_id ,string hidden, std::string request_id){
    // char* wd;
    // getwd(wd);
    std::string path = std::string(get_current_dir_name()) + "/images/mine/" + to_string(image_id)+ ".jpg";
    std::string temp_path = std::string(get_current_dir_name())  + "/images/stego/" + to_string(image_id)+ "_stego.jpg";
    // get hidden text from DB
    std::string hidden_text = hidden;

    std::string stego_image = stega_encode(path, hidden_text, temp_path);
    std::cout << stego_image ;
    requestInfo reqinfo = {
        .image_id=image_id,
        .request_id= request_id,
        .owner_ip="",
        .owner_name="",
        .p_message= stego_image,
        .operation = SendImage,
        .rpc_id = 5,
        .msg_type = Reply
    };

    Message msg = Message(reqinfo);
    std::cout << msg ;
    return msg;
}

void Server::updateCount(int image_id, int num_views){
    std::string image_path =std::string(get_current_dir_name())  + "/images/requested/" + to_string(image_id) + ".jpg";
    std::string output = stega_decode(image_path);
    int sep_index = output.find(',');
    std::string tempPath =std::string(get_current_dir_name())  + "/images/stego/temp.jpg";
    std::string new_text = to_string(num_views) + output.substr(sep_index);
    printf("New Count is : %s \n" , new_text.c_str());
    stega_encode(image_path, new_text, tempPath);
    copyImage(tempPath, image_path);
}

void Server::dispatch(Message & msg){
    printf("Request Number: %i\n", msg.getOperation());
    int image_id = msg.getImageId();
    std::string request_id = msg.getRequestId();

    std::string username="Manar";
    switch (msg.getOperation()){
        case SendImage: { // an image with a specified id
            int image_id = msg.getImageId();
            int num_views = rand()%10+1;
            Message m = buildImageMsg(image_id , to_string(num_views)+","+myName+","+hostname, request_id);
            reqReply->sendReply(m);
            std::tuple<std::string, int> userInfo(username, num_views); //add to db
            db->insertUser(image_id, userInfo);
            break;
        }
        case SendSample :{ // send three samples
            for(int i=0; i<3; i++){
                Message msg = buildImageMsg(i ,(string) port+","+hostname, request_id);
                reqReply->sendReply(msg);
                sleep(5);
            }
            break;
        }
        case SendImages: { // an image with a specified id
            int no_views = 5; //default
            for(int i=0; i<6; i++){
                Message msg = buildImageMsg(i , (string)port+","+hostname, request_id);
                reqReply->sendReply(msg);
                sleep(5);
                /*//add in db
                std::tuple<std::string, int> t(username,no_views);
                db->insertUser(std::to_string(image_id),t);*/
            }
            break;
        }
        case ViewAccess:{ // updates view count embedded inside an image
            int num_views = atoi(msg.getMessage().c_str());
            updateCount(image_id, num_views);
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
    string toConnectIp ;
    string toConnectPort ;
    int r = rand()%((65535 - 4040) + 1) + 4040;
    Message msg = Message();
    reqReply->getReq(msg);
    std::cout<<"entered          "<<endl;
    int reqNum = msg.getMessageType() ;
    int image_id= msg.getImageId();
    Thread * thrd = new Thread(false , true ,  reqNum ,image_id,  serverName, r ,  toConnectIp , toConnectPort, 0); //server thread
    printf("Data Recieved:%s \n", msg.getMessage().c_str()); // msg received

    dispatch(msg);
    return 1;
}

Server::~Server(){
    reqReply->shutDownFD();
}
