#include "../headers/RequestReply.h"
#include "../headers/Message.h"
#include <fcntl.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

RequestReply::RequestReply(const char *destinationPort, const char *destinationIp, bool isClient, bool isTimeout, int buff_size) {

    port = atoi(destinationPort);



    if(isClient){
        socketfd = socket(AF_INET, SOCK_STREAM, 0);
        if (socketfd < 0)
            error("ERROR opening socket");

        server = gethostbyname(destinationIp);
        if (server == NULL) {
            fprintf(stderr,"ERROR, no such host\n");
            exit(0);
        }

        //setting up connection
        bzero((char *) &serverAddr, sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        bcopy((char *)server->h_addr,
              (char *)&serverAddr.sin_addr.s_addr,
              server->h_length);
        serverAddr.sin_port = htons(port);

        if (connect(socketfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0)
            error("ERROR connecting");


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
        socketfd =  socket(AF_INET, SOCK_STREAM, 0); //create socket
        if (socketfd < 0)
            error("ERROR opening socket");

        bzero((char *) &serverAddr, sizeof(serverAddr));

        port = atoi(destinationPort);


        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_port = htons(port);


        if (bind(socketfd, (struct sockaddr *) &serverAddr,
                 sizeof(serverAddr)) < 0)
            error("ERROR on binding");


        listen(socketfd,5);
        puts("Waiting for incoming connections...");
    }
    
    if(socketfd  <0) {
        perror("socket failed");
    }
    this->isClient = isClient;
    this->isTimeout = isTimeout;
    this->buff_size = buff_size;
}

int RequestReply::doOperation(char buffer []){
    packet_index = 1;

    picture = fopen(buffer, "r");
    printf("Getting Picture Size\n");

    if(picture == NULL)
    {
        printf("Error Opening Image File");
    }
    else
    {

        //Get Image Size
        fseek(picture, 0, SEEK_END);
        size = ftell(picture);
        fseek(picture, 0, SEEK_SET);
        printf("Total Picture size: %i\n",size);

        //Send Picture Size
        printf("Sending Picture Size\n");
        stat = write(socketfd, (void *)&size, sizeof(int));
        ///Timeout Check
        int n = 0;
        if (stat<=0)
            n =5;
        while (stat<=0){
            std::cout << "I am trying again "<< std::endl;
            if (n>0){
                stat = write(socketfd, send_buffer, read_size);
                n--;
            }
            else {break;}
        }
        if(stat<=0)
        {
            perror("Send Failed with status ");
            return stat;
        }
        else
            perror("Send Succeeded ");
        //////////

        //Send Picture as Byte Array
        printf("Sending Picture as Byte Array\n");

        do
        { //Read while we get errors that are due to signals.
            stat=read(socketfd, &read_buffer , 255);
            printf("Bytes read: %i\n",stat);
        } while (stat < 0);


        while(!feof(picture))
        {
            //Read from the file into our send buffer
            read_size = fread(send_buffer, 1, sizeof(send_buffer) - 1, picture);

            //Send data through our socket
            stat = write(socketfd, send_buffer, read_size);

            ///Timeout Check
            int n = 0;
            if (stat<=0)
                n =5;
            while (stat<=0){
                std::cout << "I am trying again "<< std::endl;
                if (n>0){
                    stat = write(socketfd, send_buffer, read_size);
                    n--;
                }
                else {break;}
            }

            if(stat<=0) {
                perror("Send Failed with status ");
                return stat;
            }
            //////////

            printf("Packet Number: %i\n", packet_index);
            printf("Packet Size Sent: %i\n", read_size);
            printf(" \n");
            printf(" \n");

            packet_index++;
            //Zero out our send buffer
            bzero(send_buffer, sizeof(send_buffer));
        }
        return 1;
    }
}

int receive_image(int socket) { // Start function

    int buffersize = 0, recv_size = 0, size = 0, read_size, write_size, packet_index = 1, stat;

    char imagearray[10241], verify = '1';
    FILE *image;

//Find the size of the image
    do {
        stat = read(socket, &size, sizeof(int));
    } while (stat < 0);

    printf("Packet received.\n");
    printf("Packet size: %i\n", stat);
    printf("Image size: %i\n", size);
    printf(" \n");

    char buffer[] = "Got it";

//Send our verification signal
    do {
        stat = write(socket, &buffer, sizeof(int));
    } while (stat < 0);

    printf("Reply sent\n");
    printf(" \n");

    image = fopen("Winnie_Pooh.jpg", "w");

    if (image == NULL) {
        printf("Error has occurred. Image file could not be opened\n");
        return -1;
    }

//Loop while we have not received the entire file yet

    int need_exit = 0;
    struct timeval timeout = {10, 0};

    fd_set fds;
    int buffer_fd, buffer_out;

    while (recv_size < size && read_size != 0) {

        FD_ZERO(&fds);
        FD_SET(socket, &fds);

        buffer_fd = select(FD_SETSIZE, &fds, NULL, NULL, &timeout);

        if (buffer_fd < 0)
            printf("error: bad file descriptor set.\n");

        if (buffer_fd == 0)
            printf("error: buffer read timeout expired.\n");

        if (buffer_fd > 0) {
            do {
                read_size = read(socket, imagearray, 10241);
            } while (read_size < 0);

            printf("Packet number received: %i\n", packet_index);
            printf("Packet size: %i\n", read_size);


            //Write the currently read data into our image file
            write_size = fwrite(imagearray, 1, read_size, image);
            printf("Written image size: %i\n", write_size);

            if (read_size != write_size) {
                printf("error in read write\n");
            }


            //Increment the total number of bytes read
            recv_size += read_size;
            packet_index++;
            printf("Total received image size: %i\n", recv_size);
            printf(" \n");
            printf(" \n");
        }

    }

    fseek(image, 0, SEEK_END);
    size = ftell(image);
    if (size > 0)
        {
        printf("Total Picture size: %i\n", size);
        printf("Image successfully Received!\n");
        }
    else
        printf("Image Not Received!\n");



    fclose(image);

    return 1;
}

int RequestReply::getRequest(char buffer []) {

    clilen = sizeof(cli_addr);


    newsockfd = accept(socketfd,
                       (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0)
        error("ERROR on accept");

    printf("server: got connection from %s port %d\n",
           inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));

    receive_image(newsockfd);
}

void RequestReply::setBuffSize(int size){
    buff_size = size;
}
int RequestReply::sendReply(char buffer []) {
    /*Message m = Message(buffer, strlen(buffer));
    m.setMessageType(MessageType(Reply));
    char * marshalled = m.marshal();*/
    int replyStatus = write(newsockfd, buffer, strlen(buffer));
   // if (isTimeout){
       // std::cout<<"timeout reply"<<std::endl;
        int n = 0;
        if (replyStatus<=0)
                n =5;
        while (replyStatus<=0){
            if (n>0){
             replyStatus =write(newsockfd, buffer, strlen(buffer));
                n--;
            }
            else {
                break;
            }
        }
    //}
   
    if(replyStatus<0)
    {
        perror("Could not Reply to Sender with status ");
    }
    else
        printf("Sent Reply");

    return replyStatus;
}
int RequestReply::getReply(char buffer []) {
    int recStatus  = read(socketfd, buffer, sizeof(int));
    ///Timeout Check

    int n = 0;
    if (recStatus<=0)
        n =20;
    while (recStatus<=0){
        std::cout << "I am trying again "<< std::endl;
        if (n>0){
            recStatus = read(socketfd, buffer, sizeof(int));
            n--;
        }
        else {
            break;
        }
    }


    if(recStatus<=0) {
        perror("Could not Receive Message with status ");
    }
    else {
        printf("Server Replied\n");
    }

    return recStatus;

}
void RequestReply::shutDownFD() {
    shutdown(socketfd , SHUT_RDWR);
}