#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc,char **argv) // client
{

     printf("port: %s \n", argv[1]);
    printf("address: %s \n", argv[2]);

    int port = atoi(argv[1]); //change to access client from different pc 
    int socketfd;
    char buffer [1024];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    socketfd = socket(PF_INET,SOCK_DGRAM,0); // define socket
    memset(&serverAddr,'\0',sizeof(serverAddr));

    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(port);
    serverAddr.sin_addr.s_addr = inet_addr((argv[2])); //change to access client from different pc 
    
    do {
        //fflush(stdin);
        printf("Enter message:");
        scanf("%s",buffer );
        sendto(socketfd, buffer, 1024, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
        //printf("Data Send: %s \n", buffer);
        recvfrom(socketfd,buffer,1024,0,(struct sockaddr*)&serverAddr, &addr_size);
        printf("%s \n", buffer);

    } while (strcmp (buffer,"Q") !=0  );

    return 0;
}