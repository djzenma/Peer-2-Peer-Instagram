#include "../headers/RequestReply.h"
#include "../headers/Message.h"
#include <fcntl.h>


RequestReply::RequestReply(const char * IP){

    port = 4040;
    memset(&serverAddr,'\0',sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(IP);
    socketfd = socket(AF_INET,SOCK_DGRAM,0);
    //serverAddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(socketfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == 0)
            printf("\nSuccessfully binded!\n");
    else
            printf("\nBinding Failed!\n");


    if(socketfd  <0) {
        perror("socket failed");
    }
    buff_size = BUFF_SIZE; // check if this laptop issue
   
    recThread = std::thread(&RequestReply::rec,this);
    recThread.detach();

}

void RequestReply::send(argsSend a)
{
    serverAddr.sin_addr.s_addr = inet_addr(a.IP);

    for (int i=0; i<a.packets.size();i++)
    {
        //printf("Sending Packet %d: \n ", i);
        int res = static_cast<int>(sendto(socketfd, (void *)a.packets[i].marshal().c_str(), buff_size, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr))); 
        int num_retries = NUM_RETRIES;
        while(res < 0 && num_retries != 0){ // retry sending the packet if failed
            std::cout << "Retrying again  " << std::endl; 
            res = static_cast<int>(sendto(socketfd, (void *)a.packets[i].marshal().c_str(), buff_size, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr))); 
            num_retries--;
        }
    }
    a.res = 1;
}
std::string RequestReply::sendMessage(Message & m, const char* IP){
    argsSend a;
    a.IP=IP;
    a.isEmpty = false;
    
    m.setIP(std::string(IP));

    std::vector<Message> packets = createPackets(m);
    a.packets= packets;
   
    sendThread = std::thread(&RequestReply::send,this,a);
    sendThread.join();
    if(a.res >=0){
        return "ok";
    }
    return "";
}

void RequestReply::rec()
{
    //call rec thread in constructor - to always listen
   //place stuff in vector

    addr_size = sizeof(serverAddr);
    do {
         stat = recv(socketfd,read_buffer, buff_size,0);
        // std::cout<<"Receive stat "<< stat<<std::endl;
           
         if(stat >= 0){
            std::string marshalled = std::string(read_buffer);
            Message recieved_msg = Message(marshalled);
            std::string msg_id = recieved_msg.getRequestId();
            
            //std::cout <<  "Received: " << recieved_msg.getRequestId() << std::endl;
            std::cout << "Received Packet: " << recieved_msg.getPacketIndex()
                      << "from : " << recieved_msg.getTotalPackets() << std::endl;


            if(chunked_msgs.count(msg_id) == 0){ // check if msg doesn't exist
                printf("Msg doesn't exist \n");
                chunked_msgs[msg_id].push_back(recieved_msg);
                // check if the first packet is the last one 
                if(recieved_msg.getPacketIndex() == recieved_msg.getTotalPackets()){
                    printf("Inserting in Buffer \n");
                    mlock.lock();
                    rec_buffer.push_back(recieved_msg);
                    mlock.unlock();
                }
            }
            else{ // if it exists
                if (chunked_msgs[msg_id].back().getPacketIndex() == recieved_msg.getPacketIndex()-1){
                    chunked_msgs[msg_id].push_back(recieved_msg);
                    printf("inserting chunk \n");
                    if(recieved_msg.getPacketIndex() == recieved_msg.getTotalPackets()-1){ // if recieved packet is the last one
                        std::string marshalled = "";
                        for(int i=0; i< chunked_msgs[msg_id].size(); i++){
                            marshalled = marshalled + chunked_msgs[msg_id][i].getMessage();
                        }
                        Message complete = Message(marshalled);

                        mlock.lock();
                        printf("inserting complete msg \n");
                        rec_buffer.push_back(complete);
                        mlock.unlock();
                    }
                }
                else{
                    std::cout << "Packet is dropped or packets out of order"  <<std::endl; 
                }
                
            }
           
           
         }

        } while (true);
}
//recv from all in buff
//get form buff ip
int RequestReply::recReply(Message & m, std::string request_id){
    mlock.lock();

    if(rec_buffer.size() == 0){
        //printf("No Pending Messages \n");
        mlock.unlock();
        return 0;
    }

    printf("Pending Messages : %d\n", rec_buffer.size());

    for (int i=0; i< rec_buffer.size(); i++){
        std::cout << rec_buffer[i] << std::endl;
        if(rec_buffer[i].getRequestId() == request_id && rec_buffer[i].getMessageType()==Reply){
            std::cout << rec_buffer[i] << std::endl;
            m = rec_buffer[i];
            rec_buffer.erase(rec_buffer.begin() + i);
            mlock.unlock();
            return 1;
        }
    }
    mlock.unlock();

    return 0;
           
}

int RequestReply::recRequest(Message & m){
    mlock.lock();

    if(rec_buffer.size() == 0){
        //printf("No Pending Messages \n");
        mlock.unlock();
        return 0;
    }

   // printf("Pending Messages : %d\n", rec_buffer.size());

    for (int i=0; i< rec_buffer.size(); i++){
        if(rec_buffer[i].getMessageType()==Request){
            std::cout << rec_buffer[i] << std::endl;
            m = rec_buffer[i];
            rec_buffer.erase(rec_buffer.begin() + i);
            mlock.unlock();
            return 1;
        }
    }
    mlock.unlock();

    return 0;
}



std::vector<Message> RequestReply::createPackets(Message & m ){
    std::vector<Message> packets;

    int index = 0;

    std::string marshalled = m.marshal(); 
    int msg_size = marshalled.length();
    int num_packets =  ceil((float) msg_size/ buff_size);
    
    printf("msg_size %i: , send_buffer %i , packets: %i \n", msg_size, buff_size, num_packets );

    while (index != num_packets-1){
        std::string msg = marshalled.substr(index++ * buff_size, buff_size);
        Message packet = m;
        packet.setMessage(msg, msg.length()); 
        packet.setPacketIndex(index);  // packet number
        packet.setTotalPacket(num_packets);
        packets.push_back(packet);
    }

    std::string msg = marshalled.substr(index * buff_size);

    Message packet = m;
    packet.setMessage(msg, msg.length()); 
    packet.setPacketIndex(++index);  // final packet number
    packet.setTotalPacket(num_packets);
    packets.push_back(packet);
    
    return packets;
}
