#include "../headers/RequestReply.h"
#include "../headers/Message.h"
#include <fcntl.h>


RequestReply::RequestReply(const char * IP){

    port = 4040;
    myIP = IP;
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


    if(socketfd<0) {
        perror("socket failed");
    }
    buff_size = BUFF_SIZE; // check if this laptop issue
   
    recThread = std::thread(&RequestReply::rec,this);
    recThread.detach();

}

void RequestReply::send(argsSend a)
{
    serverAddr.sin_addr.s_addr = inet_addr(a.IP);
    // Message ack_msg = Message::buildAckMsg(a.packets[0]);
    // a.packets.push_back(ack_msg);

    for (int i=0; i<a.packets.size();i++)
    {
        std::cout << "Sending Packet %d: \n " << a.packets[i].getPacketIndex() << std::endl;
        int num_retries = NUM_RETRIES;
        bool recieved = false;

        std::string packet = a.packets[i].marshal();

        do {
            int res = static_cast<int>(sendto(socketfd, (void *)packet.c_str(), packet.length()+1, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr))); 

            if(res < 0)
                printf("Failed to send packet %d", i);
            else recieved = true;
            num_retries--;
            
        } while(num_retries != 0 && !recieved);

        if(!recieved){
            printf("Failed Sending Message \n");
            break;
        }
    }
    a.res = 1;
}
std::string RequestReply::sendMessage(Message & m, const char* IP){
    argsSend a;
    a.IP=IP;
    a.isEmpty = false;
    
    m.setIP(myIP);

    std::vector<Message> packets = createPackets(m);
    a.packets= packets;
   
    sendThread = std::thread(&RequestReply::send, this, a);
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
         //std::cout<<"Receive stat "<< stat<<std::endl;
           
         if(stat >= 0){
            std::string marshalled = std::string(read_buffer);
            Message recieved_msg = Message(marshalled);
            std::string msg_id = recieved_msg.getRequestId();
            
             std::cout << "Received Packet: \n" << recieved_msg.getPacketIndex() << std::endl;
            //           << "from : " << recieved_msg.getTotalPackets() << std::endl;


            // if(recieved_msg.getMessageType()==ACK){ // recieved an aknowledgment for a message I sent.
            //     printf("Recieved an ACK for %s \n", recieved_msg.getRequestId().c_str());
            //     ack_lock.lock();
            //     acks[recieved_msg.getRequestId()] = recieved_msg;
            //     ack_lock.unlock();
            //     continue;
            // }
            /*
                SEND ACK
            */

            // Message ack_msg = Message::buildAckMsg(recieved_msg);
            // printf("Sending an ACK MSG with: %s", ack_msg.getRequestId().c_str());

            // serverAddr.sin_addr.s_addr = inet_addr(recieved_msg.getIP().c_str());
            // int res = static_cast<int>(sendto(socketfd, (void *)ack_msg.marshal().c_str(), buff_size, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr))); 

            /*
                INSERT RECIEVED MSG IN BUFFER
            */
            if(chunked_msgs.count(msg_id) == 0){ // check if msg doesn't exist
                chunked_msgs[msg_id] = std::vector<Message>(recieved_msg.getTotalPackets());
                chunked_msgs[msg_id][recieved_msg.getPacketIndex()-1] =recieved_msg;
                // check if the first packet is the last one 
                if(recieved_msg.getPacketIndex() == recieved_msg.getTotalPackets()){
                    printf("Inserting in Buffer \n");
                    std::string marshalled = recieved_msg.getMessage();
                    Message complete = Message(marshalled);
                    mlock.lock();
                    rec_buffer.push_back(complete);
                    mlock.unlock();
                }
            }
            else{ // if it exists
                chunked_msgs[msg_id][recieved_msg.getPacketIndex()-1] =recieved_msg;
                printf("inserting chunk \n");
                if(recieved_msg.getPacketIndex() == recieved_msg.getTotalPackets()){ // if recieved packet is the last one
                    std::string marshalled = "";
                    for(int i=0; i< chunked_msgs[msg_id].size(); i++){
                        if(!chunked_msgs[msg_id][i].getRequestId().empty())
                            marshalled = marshalled + chunked_msgs[msg_id][i].getMessage();
                        else printf("Dropped Packet :  %d \n", i);
                    }
                    Message complete = Message(marshalled);
                    std::cout << "Complete: " << complete << std::endl;
                    mlock.lock();
                    printf("Inserting complete msg \n");
                    rec_buffer.push_back(complete);
                    mlock.unlock();
                }
            }
         }

    } while (true);
}

bool RequestReply::recieveACK(Message & packet){
    std::string ack_id = packet.getRequestId() + std::to_string(packet.getPacketIndex()) + std::to_string(packet.getTotalPackets());
    bool recieved = false;
    printf("Searching for : %s: ", ack_id.c_str());
    ack_lock.lock();
    if(acks.count(ack_id) > 0){
        recieved = true;  
        acks.erase(ack_id);  
    }   
    ack_lock.unlock();
    return recieved;
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
        if(rec_buffer[i].getRequestId() == request_id && rec_buffer[i].getMessageType()==Reply){
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

    printf("Pending Messages : %d\n", rec_buffer.size());

    for (int i=0; i< rec_buffer.size(); i++){
        if(rec_buffer[i].getMessageType()==Request){
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
    int send_buff = buff_size - 114;
    std::string marshalled = m.marshal(); 
    int msg_size = marshalled.length();
    int num_packets =  ceil((float) msg_size/ (send_buff));
    
    printf("msg_size %i: , send_buffer %i , packets: %i \n", msg_size, send_buff, num_packets );

    while (index != num_packets-1){
        std::string msg = marshalled.substr(index++ * send_buff, buff_size);
        Message packet = m;
        packet.setMessage(msg, msg.length()); 
        packet.setPacketIndex(index);  // packet number
        packet.setTotalPacket(num_packets);
        packets.push_back(packet);
    }

    std::string msg = marshalled.substr(index * send_buff);

    Message packet = m;
    packet.setMessage(msg, msg.length()); 
    packet.setPacketIndex(++index);  // final packet number
    packet.setTotalPacket(num_packets);
    packets.push_back(packet);
    
    return packets;
}
