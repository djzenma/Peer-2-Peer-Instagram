#include "../headers/RequestReply.h"
#include "../headers/Message.h"
#include <fcntl.h>


RequestReply::RequestReply(const char *destinationPort, const char *destinationIp, bool isClient, int buff_size) {

    port = atoi(destinationPort);

    memset(&serverAddr,'\0',sizeof(serverAddr));


    if(isClient){

        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);
        serverAddr.sin_addr.s_addr = inet_addr(destinationIp);

        socketfd = socket(AF_INET,SOCK_DGRAM,0);

        // set timeout on client
        struct timeval tv;
        tv.tv_sec = 0.5;
        tv.tv_usec = 100;

        if (setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof (tv)) < 0)
            perror("setsockopt failed\n");

        if (setsockopt(socketfd, SOL_SOCKET,  SO_SNDTIMEO, (const char*)&tv, sizeof (tv)) < 0)
            perror("setsockopt failed\n");

    }
    else {
        serverAddr.sin_family=AF_INET;
        serverAddr.sin_port=htons(port);
        serverAddr.sin_addr.s_addr = INADDR_ANY;

        socketfd = socket(AF_INET,SOCK_DGRAM,0);

        if (bind(socketfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == 0)
            printf("\nSuccessfully binded!\n");
        else
            printf("\nBinding Failed!\n");
    }

    if(socketfd  <0) {
        perror("socket failed");
    }
    this->isClient = isClient;
    this->buff_size = buff_size;
}

int RequestReply::sendReq (Message & m){ //send request number


    int sendStatus = static_cast<int>(sendto(socketfd, (void *)m.marshal().c_str(), buff_size, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr)));

    ///Timeout Check
    int n = 0;
    if (sendStatus<=0)
        n =5;
    while (sendStatus<=0){
        std::cout << "I am trying again "<< std::endl;
        if (n>0){
            int sendStatus = static_cast<int>(sendto(socketfd, (void *)m.marshal().c_str(), buff_size, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr)));
            n--;
        }
        else {break;}
    }


    if(sendStatus<=0) {
        perror("Send Failed with status ");
    }
    else
        printf("\n---------Data Received---------\n");
    return sendStatus;
}

int RequestReply::getReq(Message & msg) {
    addr_size = sizeof(serverAddr);

    do {
         stat = recvfrom(socketfd,read_buffer, buff_size,0,(struct sockaddr*)&serverAddr, &addr_size);

    } while (stat < 0);
    std::string marshalled = std::string(read_buffer);
    msg = Message(marshalled);

    return stat;
}

int RequestReply::sendReply(Message & m){

    int packet_index = 1;
    std::string marshalled = m.marshal();
    int msg_size = marshalled.length();

    // Divide msg into chunks
    int chunks = ceil((float)msg_size / sizeof(send_buffer));
    printf("msg_size %i: , send_buffer %i , chunks: %i \n", msg_size, sizeof(send_buffer), chunks );

    float n1 = (float)marshalled.length() ;
    int n2 = sizeof(send_buffer);

    //float rem = remainder((float)marshalled.length() , sizeof(send_buffer)) ;
    int rem = n1-(n1/n2)*n2 ;
    printf("Message size after Marshalling : %i, Dividing to : %i\n", msg_size,chunks );

    printf("Sending Message Size\n");
    int sendStatus = static_cast<int>(sendto(socketfd, (void *)&msg_size, sizeof(int), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr)));
    int index = 0;
    while(chunks!=0){
        std::string chunkedImage;
        if(chunks == 1){
            chunkedImage = marshalled.substr(index * sizeof(send_buffer));
        }
        else{
            chunkedImage = marshalled.substr(index * sizeof(send_buffer), sizeof(send_buffer));
        }
        printf("lenght : %i: , %i \n", chunkedImage.length(), marshalled.length());
        strcpy(send_buffer , chunkedImage.c_str());

        //Send data through our socket
        if (chunks==1 && rem !=0) // last chunk
            read_size=rem ;
        else
            read_size=sizeof(send_buffer);

        int sendStatus = static_cast<int>(sendto(socketfd, (void *)send_buffer, read_size, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr)));
        ///Timeout Check
        int n = 0;
        if (sendStatus<=0)
            n =5;
        while (sendStatus<=0){
            std::cout << "I am trying again to send packet"<< std::endl;
            if (n>0){
                int sendStatus = static_cast<int>(sendto(socketfd, (void *)send_buffer, read_size, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr)));
                n-- ;
            }
            else {break;}
        }
        if(sendStatus<=0) {
            perror("Send Failed with status ");
            return sendStatus;
        }


        total_size += read_size;

        printf("Packet Number: %i\n", packet_index);
        printf("Packet Size Sent: %i\n", read_size);
        printf("Sent: %i of the message\n", total_size);
        printf(" \n");
        printf(" \n");

        index++;
        packet_index++;
        chunks--;
        //Zero out our send buffer
        bzero(send_buffer, sizeof(send_buffer));
        sleep(1);
    }
    chunks= 0 ;
    return 1;

}

int RequestReply::getReply(Message & m) {


    int buffersize = 0, recv_size = 0, size = 0, read_size = -1, write_size, packet_index = 1, stat;

    char recieve_buff[10241], verify = '1';
    FILE *image;

    //Find the size of the message
    do {
        stat = recvfrom(socketfd,&size, sizeof(int),0,(struct sockaddr*)&serverAddr, &addr_size);
    } while (stat < 0);

    printf("Packet received.\n");
    printf("Packet size: %i\n", stat);
    printf("Message size: %i\n", size);
    printf(" \n");

    //Loop while we have not received the entire file yet

    struct timeval timeout = {100000000000, 0};

    fd_set fds;
    int buffer_fd;

    std::string recieved_msg = "";
    int index = 1;
    while (recv_size < size &&  read_size != 0 ) {

        FD_ZERO(&fds);
        FD_SET(socketfd, &fds);

        buffer_fd = select(FD_SETSIZE, &fds, NULL, NULL, &timeout);

        if (buffer_fd < 0)
            printf("error: bad file descriptor set.\n");

        if (buffer_fd == 0)
            printf("error: buffer read timeout expired.\n");

        if (buffer_fd > 0) {
            do {
                read_size = recvfrom(socketfd,recieve_buff, sizeof(recieve_buff),0,(struct sockaddr*)&serverAddr, &addr_size);
            } while (read_size < 0);

            std::string chunked_msg = std::string(recieve_buff, read_size);
            recieved_msg = recieved_msg + chunked_msg;

            printf("Packet number received: %i\n", index++);
            printf("Packet size: %i\n", read_size);

            //Increment the total number of bytes read
            recv_size += read_size;
            std::cout << "r " << recv_size << std::endl;
            packet_index++;
            printf("Total received msg size: %i\n", recv_size);
            printf(" \n");
        }

    }
    std::cout << " recieve size " << recieved_msg.length() << " size :  " << size <<   std::endl;
    if (recieved_msg.length() >= size && size != 0)
    {
        printf("Total Message size: %i\n", recieved_msg.length());
        m = Message(recieved_msg);
        std::string temp_loc = "/home/manar/Desktop/Distributed-Client/client2.jpg";
        std::ofstream outFile;
        outFile.open(temp_loc);
        outFile << m.getMessage();
        outFile.close();

        return 1;
    }
    else {
        printf("Message Not Received!\n");
        return -1;
    }
}
void RequestReply::shutDownFD() {
    shutdown(socketfd , SHUT_RDWR);
}
