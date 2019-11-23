//
// Created by Mazen on 16.11.19.
//

#include "../headers/Communication.h"
#include "../headers/DoS.h"


Communication::Communication() {
    reset();
}

void Communication::reset(){
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
    }
}


/* From Client To Server
 * Send text msg
 * Returns Response
 */
char* Communication::sendMsg(const char * IP, const int PORT, char* msg) {
    int valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    reset();
    // Destination
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(IP);
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, IP, &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return "";
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return "";
    }

    send(sock , msg , strlen(msg) , 0);
    printf("Com: Sent Message\n");
    valread = read( sock , buffer, 1024);
    printf("Com: Response: %s\n", buffer);
    return buffer;
}



/* Initializes Socket to send to arg "ip"
 */
int Communication::init_imaging_socket(std::string dest_ip) {

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
        perror("ERROR opening socket");

    peer = gethostbyname(dest_ip.c_str());
    if (peer == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    //setting up connection
    bzero((char *) &peerAddr, sizeof(peerAddr));

    /*
    peerAddr.sin_family = AF_INET;
    bcopy((char *)peer->h_addr,
          (char *)&peerAddr.sin_addr.s_addr,
          peer->h_length);
    peerAddr.sin_port = htons(port);
*/
    peerAddr.sin_family = AF_INET;
    peerAddr.sin_addr.s_addr = inet_addr(dest_ip.c_str());
    peerAddr.sin_port = htons(AUTH_PORT);


    if (connect(socketfd, (struct sockaddr *) &peerAddr, sizeof(peerAddr)) < 0)
        std::cout<<"ERROR connecting\n";//perror("ERROR connecting");

    // set timeout on client
    struct timeval tv;
    tv.tv_sec = 0.5;
    tv.tv_usec = 100;

    if (setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof (tv)) < 0)
        perror("setsockopt failed\n");

    if (setsockopt(socketfd, SOL_SOCKET,  SO_SNDTIMEO, (const char*)&tv, sizeof (tv)) < 0)
        perror("setsockopt failed\n");
}


/*
    constructs image msg given an image id
*/
Message Communication::buildImageMsg(int image_id, std::string owner_ip, std::string owner_name) {
    // TODO
    std::string path =
            "../images/mine/" + std::to_string(image_id) + ".jpg";
    std::string temp_path =
            "../images/stego/" + std::to_string(image_id) + "_stego.jpg";
    // get hidden text from DB
    std::string hidden_text = "Secrets";
    std::string stego_image = stega_encode(path, hidden_text, temp_path);
    requestInfo reqinfo = {
            .image_id=image_id,
            .storage_location="",
            .p_message= stego_image,
            .operation = 0,
            //.owner_ip = owner_ip,
            //.owner_name = owner_name
            //.rpc_id = 5,
            //.msg_type = Reply
    };

    Message msg = Message(reqinfo);
    return msg;
}

// socket creation & binding
// Returns socketfd, address
Communication::Transaction Communication::init_socket(const char *LISTEN_IP, const int LISTEN_PORT) {
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }


    // Forcefully attaching socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(LISTEN_IP);
    //address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( LISTEN_PORT );

    //bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    // Forcefully attaching socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    Communication::Transaction tx;
    tx.address = address;
    tx.server_fd = server_fd;
    return tx;
}



/*
 * Listen For Requests
 */
int Communication::listenTx(Communication::Transaction tx, char* req) {
    int new_socket, valread;
    int addrlen = sizeof(tx.address);

    if (listen(tx.server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(tx.server_fd, (struct sockaddr *)&tx.address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    valread = read( new_socket , req, 1024);
    return new_socket;
}


// UDP
int Communication::sendImage(Message &m, std::string destIp){
    int port, socketfd;
    struct sockaddr_in serverAddr, si_other;


    // Construct
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(AUTH_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(destIp.c_str());

    socketfd = socket(AF_INET,SOCK_DGRAM,0);

    // set timeout on client
    struct timeval tv;
    tv.tv_sec = 0.5;
    tv.tv_usec = 100;

    if (setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof (tv)) < 0)
        perror("setsockopt failed\n");

    if (setsockopt(socketfd, SOL_SOCKET,  SO_SNDTIMEO, (const char*)&tv, sizeof (tv)) < 0)
        perror("setsockopt failed\n");

    // **


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

int Communication::getImage(Message &m) {
    int port, socketfd;
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    // Construct
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(AUTH_PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    socketfd = socket(AF_INET,SOCK_DGRAM,0);

    if (bind(socketfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == 0)
        printf("\nSuccessfully binded!\n");
    else
        printf("\nBinding Failed!\n");

    // **

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

    struct timeval timeout = {2000, 0};

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