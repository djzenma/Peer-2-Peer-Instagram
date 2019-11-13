#include "../headers/RequestReply.h"
#include "../headers/Message.h"
#include <fcntl.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

RequestReply::RequestReply(const char *destinationPort, const char *destinationIp, bool isClient,  int buff_size) {

    port = atoi(destinationPort);



    if(!isClient){
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


        clilen = sizeof(cli_addr);

        newsockfd = accept(socketfd,
                           (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0)
            error("ERROR on accept");

        printf("server: got connection from %s port %d\n",
               inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));

    }

    if(socketfd  <0) {
        perror("socket failed");
    }
    this->isClient = isClient;
    this->buff_size = buff_size;


}
int RequestReply :: sendImage (std::string s)
{
    packet_index = 1;

   /* char buffer [s.size()+1]  ;
    strcpy(buffer , s.c_str());
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
        fseek(picture, 0, SEEK_SET);*/

        std::string image_loc = s;
        std::string temp_loc = "/Users/owner/CLionProjects/Distributed-Client/Manar/temp.jpeg";

        std::string hidden_text = "Manar: 3, Aya: 5";
        std::string stego_image = stega_encode(image_loc, hidden_text, temp_loc);
        requestInfo reqinfo ={.image_id=1,
                .storage_location="manar",
                .p_message= stego_image,
                .operation = SendImage,
                .rpc_id = 5,
                .msg_type = Reply };

        ImageMessage msg = ImageMessage(reqinfo);
        std::string imageMarshalled =  msg.marshal();

        size = imageMarshalled.length();
        int chunks = ceil((float)size / sizeof(send_buffer));
        int rem = remainder((float)imageMarshalled.length() , sizeof(send_buffer)) ;


      printf("Total Picture size after Marshalling : %i\n",size);

        //Send Picture Size
        printf("Sending Picture Size\n");
        stat = write(socketfd, (void *)&size, sizeof(int));

        ///Timeout Check
        int n = 0;
        if (stat<=0)
            n =5;
        while (stat<=0){
            std::cout << "I am trying again to send size"<< std::endl;
            if (n>0){
                stat = write(socketfd, send_buffer, sizeof(int));
                n--;
            }
            else {break;}
        }

        if(stat<=0)
        {
            perror("Sending Size Failed with status \n");
            return stat;
        }
        else
            printf("Sending Size Succeeded \n");


        //Send Picture as Byte Array
        printf("Sending Picture as Byte Array\n");

       /* do
        { //Read while we get errors that are due to signals.
            stat=read(socketfd, &read_buffer , 255);
            //printf("Bytes read: %i\n",stat);
        } while (stat < 0);*/


        while(chunks!=0)
        {
            std::string chunkedImage = imageMarshalled.substr((packet_index-1)*sizeof(send_buffer) , packet_index*sizeof(send_buffer) );
            strcpy(send_buffer , chunkedImage.c_str());

            //Read from the file into our send buffer
            //read_size = fread(send_buffer, 1, sizeof(send_buffer) - 1, picture);

            //Send data through our socket
            if (chunks==1 && rem !=0) // last chunk
                read_size=rem ;
            else
                read_size=sizeof(send_buffer);


            stat = write(socketfd, send_buffer, read_size);


            ///Timeout Check
            int n = 0;
            if (stat<=0)
                n =5;
            while (stat<=0){
                std::cout << "I am trying again to send packet"<< std::endl;
                if (n>0){
                    stat = write(socketfd, send_buffer, read_size);

                }
                else {break;}
            }

            if(stat<=0) {
                perror("Send Failed with status ");
                return stat;
            }
            else
                printf("Sent All\n");

            total_size += read_size;

            printf("Packet Number: %i\n", packet_index);
            printf("Packet Size Sent: %i\n", read_size);
            printf("Sent: %i of the photo\n", total_size);
            printf(" \n");
            printf(" \n");

            packet_index++;
            //Zero out our send buffer
            bzero(send_buffer, sizeof(send_buffer));
            chunks--;
            sleep(0.5);
        }
        chunks= 0 ;
        return 1;
}

int RequestReply::doOperation(std::string s , int rN){

    if (rN== 0 || rN == 1)
      sendImage (s);
}


int receive_image(int socket , std::string s ) {

    int buffersize = 0, recv_size = 0, size = 0, read_size = -1, write_size, packet_index = 1, stat;

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

/*
    //Send our verification signal
    do {
        stat = write(socket, &buffer, sizeof(int));
    } while (stat < 0);*/

    char path [s.size()+1]  ;
    strcpy(path , s.c_str());

    image = fopen(path, "w");

    if (image == NULL) {
        printf("Error has occurred. Image file could not be opened\n");
        return -1;
    }

   //Loop while we have not received the entire file yet

    struct timeval timeout = {10, 0};

    fd_set fds;
    int buffer_fd;

    while (recv_size < size &&  read_size != 0 ) {

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

            std::string iA = imagearray ;

            ImageMessage m2 = ImageMessage(iA);

            std::string stego_image =  m2.getMessage();


            printf("Packet number received: %i\n", packet_index);
            printf("Packet size: %i\n", read_size);


            //Write the currently read data into our image file
           /* std::ofstream outFile;
            outFile.open(temp_loc);
            outFile << stego_image;
            outFile.close();*/
            char writtenImage [stego_image.size()+1]  ;
            strcpy(writtenImage , stego_image.c_str());

            write_size = fwrite(writtenImage, 1, read_size, image);
            std::string secret_text = stega_decode("/Users/owner/CLionProjects/Distributed-Client/Manar/temp.jpeg");

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

//    fseek(image, 0, SEEK_END);
//    size = ftell(image);
    if (recv_size == size)
    {
        printf("Total Picture size: %i\n", size);
        printf("Image successfully Received!\n");
        fclose(image);

        return 1;
    }
    else {

        printf("Image Not Received!\n");
        return 0 ;
    }




}

int RequestReply::getRequest(std::string s) {

    return receive_image(newsockfd , s);

}

void RequestReply::setBuffSize(int size){
    buff_size = size;
}
int RequestReply::sendReq(int reqNum) {
    /*Message m = Message(buffer, strlen(buffer));
    m.setMessageType(MessageType(Reply));
    char * marshalled = m.marshal();*/


    stat = write(newsockfd, (void *)&reqNum, sizeof(long));


    int n = 0;
    if (stat<=0)
        n =5;
    while (stat<=0){
        if (n>0){
            stat = write(newsockfd, (void *)&reqNum, sizeof(int));
            n--;
        }
        else {
            break;
        }
    }


    if(stat<0)
    {
        perror("Could not Message \n");
    }
    else
        printf("Sent Message \n");

    return stat;
}
int RequestReply::getReq(int & reqNum) {

    do {
        stat = read(socketfd, &reqNum, sizeof(int));
    } while (stat < 0);

    return stat;

}

int RequestReply::sendMessage(std::string msg) {
    /*Message m = Message(buffer, strlen(buffer));
    m.setMessageType(MessageType(Reply));
    char * marshalled = m.marshal();*/

    msg+= " " ;
    stat = write(newsockfd, (void *)&msg, msg.length());


    int n = 0;
    if (stat<=0)
        n =5;
    while (stat<=0){
        if (n>0){
            stat = write(newsockfd, (void *)&msg, 1024);
            n--;
        }
        else {
            break;
        }
    }


    if(stat<0)
    {
        perror("Could not Message \n");
    }
    else
        printf("Sent Message %s\n", &msg);

    return stat;
}
int RequestReply::getMessage(std::string & msg) {

    do {
        stat = read(socketfd, &msg, 2000);
    } while (stat < 0 || msg == "");

    return stat;

}

void RequestReply::shutDownFD() {
    shutdown(socketfd , SHUT_RDWR);
    shutdown(newsockfd , SHUT_RDWR);
}