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

    int port = atoi(argv[1]); 
    int socketfd;
    char buffer [1024];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    socketfd = socket(PF_INET,SOCK_DGRAM,0);
    if(socketfd  <0) 
    {
        perror("socket failed");
        return 0;
    }

    memset(&serverAddr,'\0',sizeof(serverAddr));

    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(port);
    serverAddr.sin_addr.s_addr = inet_addr((argv[2])); 
    
    do {
        //fflush(stdin);
        printf("Enter message:");
        scanf("%s",buffer );

        if(sendto(socketfd, buffer, 1024, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr))<0)
            perror("Send failed\n");

        //printf("Data Send: %s \n", buffer);

        if(recvfrom(socketfd,buffer,1024,0,(struct sockaddr*)&serverAddr, &addr_size)==-1)
            perror("Did not Receive reply From Server") ;
        

        printf("%s \n", buffer); //reply from server

    } while (strcmp (buffer,"q") !=0  );

    return 0;
}