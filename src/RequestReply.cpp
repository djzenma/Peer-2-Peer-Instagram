#include "../headers/RequestReply.h"
#include "../headers/Message.h"
#include <fcntl.h>

RequestReply::RequestReply(const char * IP, const int PORT){

    port = PORT;
    myIP = std::string(IP);
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

    std::ofstream out;
    out.open(" /Users/owner/CLionProjects/Distributed-Client/images/debug.txt");

    serverAddr.sin_addr.s_addr = inet_addr(a.IP.c_str());
    serverAddr.sin_port = htons(a.port);

    for (int i=0; i<a.packets.size();i++)
    {
        std::string packet = a.packets[i].marshal();
        //out << a.packets[i] << std::endl;
        std::cout << "Sending Packet: " << a.packets[i].getPacketIndex()
                  << "with size " << packet.length() << std::endl;

        int num_retries = NUM_RETRIES;
        bool recieved = false;

        
        if(packet.length()+1 > buff_size){
            std::cout << "Msg size " << packet.length()+1 << " is greater than allowed buffer size" << std::endl;
            break;
        }
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
    //out.close();
    // Send an ACK
    Message ack_msg = Message::buildAckMsg(a.packets[0]);
    Message reciever_ack = Message();

    bool dropped_packets = true;

    do{
        int ack_num_retires= NUM_RETRIES;
        bool sender_ack_recieved = false;
        bool reciever_ack_recieved = false;

        do {
            printf("Sending ack after sending packets %d:  \n", ack_num_retires);
            int res = static_cast<int>(sendto(socketfd, (void *)ack_msg.marshal().c_str(), ack_msg.marshal().length()+1, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr))); 

            if(res < 0)
                printf("Failed to send ack msg %d");
            else {
                sender_ack_recieved = true;
                /*
                    wait for ack
                */
                for (int i=0 ; i<5 && !reciever_ack_recieved ;i++){
                    printf("Wating for an ack \n");
                    sleep(1);
                    reciever_ack_recieved = recieveACK(ack_msg.getRequestId(),reciever_ack);
                }
            }
            ack_num_retires--;
            printf("Retrying to send ACK \n");
            
        } while(ack_num_retires != 0 && (!sender_ack_recieved || !reciever_ack_recieved));

        if(reciever_ack_recieved){
            std::string packets_dropped = reciever_ack.getMessage();
            std::vector<int> packets_to_resend;

            if(strcmp(packets_dropped.c_str(), ",") == 0){
                    printf("Drooped is ZERO \n");
            }
            else{
                std::string delimiter = ",";
                size_t pos = 0;
                std::string token;
                while ((pos = packets_dropped.find(delimiter)) != std::string::npos) {
                    token = packets_dropped.substr(0, pos);
                    packets_dropped.erase(0, pos + delimiter.length());
                    packets_to_resend.push_back(atoi(token.c_str()));
                }
            }
        
            if(packets_to_resend.size() == 0)
                dropped_packets = false;

            for (int i=0; i<packets_to_resend.size();i++){
                std::string packet = a.packets[packets_to_resend[i]].marshal();
                int num_retries = NUM_RETRIES;
                bool recieved = false;
                do {
                    printf("Resending : %d \n", packets_to_resend[i]);
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
        }
        else {
            printf("Failed to recieve reciever ACK \n");
            break;
        }

    }while(dropped_packets);
  
    a.res = 1;
}
std::string RequestReply::sendMessage(Message & m, const char* IP, const int PORT){
    argsSend a;
    a.IP=std::string(IP);
    a.isEmpty = false;
    a.port = PORT;

    m.setIP(myIP);

    std::vector<Message> packets = createPackets(m);
    a.packets= packets;
   
    sendThread = std::thread(&RequestReply::send, this, a);
    sendThread.detach();

    if(a.res >=0){
        return "ok";
    }
    return "";
}

void RequestReply::rec()
{
    //call rec thread in constructor - to always listen
   //place stuff in vector
    std::ofstream out;
    out.open(" /Users/owner/CLionProjects/Distributed-Client/images/rec.txt");

    addr_size = sizeof(serverAddr);
    do {
         stat = recv(socketfd,read_buffer, buff_size,0);
         std::cout<<"Receive stat "<< stat<<std::endl;

         if(stat >= 0){
            std::string marshalled = std::string(read_buffer);

            Message recieved_msg = Message(marshalled);
            std::string msg_id = recieved_msg.getRequestId();
            
            std::cout << "Received Packet: \n" << recieved_msg  << " with size "<< marshalled.size() <<  std::endl;

            if(recieved_msg.getMessageType() == ACKReply){
                printf("Got an ACK Reply from: %s\n", recieved_msg.getIP().c_str());
                ack_lock.lock();
                acks[recieved_msg.getRequestId()] = recieved_msg;
                ack_lock.unlock();
                continue;
            }

            if(recieved_msg.getMessageType()==ACK){ // recieved an aknowledgment for a message I sent.
                std::string ack_id = recieved_msg.getRequestId();
                printf("Recieved an ACK for %s \n", recieved_msg.getRequestId().c_str());
            
                std::string dropped = "";

                for(int i=0; i<chunked_msgs[msg_id].second.size() && dropped.length() < BUFF_SIZE-3000 ; i++){

                    if(chunked_msgs[msg_id].second[i].getRequestId().empty())
                        dropped = dropped  + "," +  std::to_string(i);
                }
                dropped = dropped + ",";

                if(strcmp(dropped.c_str(), ",") == 0){
                    chunked_msgs.erase(msg_id);
                }

                Message my_ack = Message::buildAckMsg(recieved_msg);
                my_ack.setMessageType(ACKReply);
                my_ack.setIP(myIP);
                my_ack.setPort(port);
                my_ack.setMessage(dropped, dropped.length());
                serverAddr.sin_addr.s_addr = inet_addr(recieved_msg.getIP().c_str());
                serverAddr.sin_port = htons(port);

                int num_retries = NUM_RETRIES;
                int res;
                do {
                     res = static_cast<int>(sendto(socketfd, (void *) my_ack.marshal().c_str(),my_ack.marshal().length() + 1, 0, (struct sockaddr *) &serverAddr,sizeof(serverAddr)));
                     num_retries -- ;
                }while(res <0 && num_retries != 0);
                printf("hnnaaa");
                continue;
            }

            /*
                INSERT RECIEVED MSG IN BUFFER
            */
            if(chunked_msgs.count(msg_id) == 0){ // check if msg doesn't exist
                // check if the first packet is the last one 
                if(recieved_msg.getPacketIndex() == recieved_msg.getTotalPackets()-1){
                    std::string packet_marshalled = recieved_msg.getMessage();
                    Message complete = Message(packet_marshalled);
                    printf("Inserting in Buffer \n");
                    mlock.lock();
                    rec_buffer.push_back(complete);
                    mlock.unlock();
                }
                else
                {
                    printf("insering \n");
                    chunked_msgs[msg_id].first = 1;
                    chunked_msgs[msg_id].second = std::vector<Message>(recieved_msg.getTotalPackets());
                    chunked_msgs[msg_id].second[recieved_msg.getPacketIndex()] =recieved_msg;
                }
            }
            else{ // if it exists
                if(chunked_msgs[msg_id].second[recieved_msg.getPacketIndex()].getRequestId().empty()){
                    chunked_msgs[msg_id].first++;
                    chunked_msgs[msg_id].second[recieved_msg.getPacketIndex()] = recieved_msg;
                    printf("inserting chunk % d\n", chunked_msgs[msg_id].first);
                    if(chunked_msgs[msg_id].first  == recieved_msg.getTotalPackets()){ // if msg is complete
                        std::string marshalled = "";

                        for(int i=0; i<chunked_msgs[msg_id].second.size(); i++){
                            out << chunked_msgs[msg_id].second[i] << std::endl;

                            if(!chunked_msgs[msg_id].second[i].getRequestId().empty())
                                marshalled = marshalled + chunked_msgs[msg_id].second[i].getMessage();
                            else{
                            // printf("Dropped Packet :  %d \n", i);
                            }
                        }
                        Message complete = Message(marshalled);
                        std::cout << "Complete: " << complete.getRequestId() << std::endl;
                        mlock.lock();
                        printf("Inserting complete msg \n");
                        rec_buffer.push_back(complete);
                        mlock.unlock();
                    }
                }
                else
                    printf("Received Duplicate \n");
            }
         }

    } while (true);
}

bool RequestReply::recieveACK(std::string ack_id, Message & ack_msg){
    bool received = false;
    ack_lock.lock();

    if(acks.count(ack_id) > 0){
        received = true;
        ack_msg = acks[ack_id];
        acks.erase(ack_id);  
    }   
    ack_lock.unlock();
    return received;
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
            std::cout << "Found : " << m << std::endl;
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
    int packet_index = 0;
    int send_buff = buff_size - 3000;
    std::string to_chunk = m.marshal();
    int msg_size = to_chunk.length();
    int num_packets =  ceil((float) msg_size/ (send_buff));

    if (num_packets==0)
        num_packets=1;

    printf("msg_size %i: , send_buffer %i , packets: %i \n", msg_size, send_buff, num_packets );

    while (index != num_packets-1){
        std::string msg = to_chunk.substr(index++ * send_buff, send_buff);
        Message packet = m;
        packet.setMessage(msg, msg.length()); 
        packet.setPacketIndex(packet_index++);  // packet number
        packet.setTotalPacket(num_packets);
        packets.push_back(packet);
    }

    std::string msg = to_chunk.substr(index * send_buff);

    Message packet = m;
    packet.setMessage(msg, msg.length()); 
    packet.setPacketIndex(packet_index++);  // final packet number
    packet.setTotalPacket(num_packets);
    packets.push_back(packet);
    
    return packets;
}


