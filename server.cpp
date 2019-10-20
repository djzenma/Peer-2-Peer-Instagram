#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;
int main(int argc,char **argv) //server
{
  
   int counter =0 ;
    printf("port: %s \n", argv[1]);
    printf("address: %s \n", argv[2]);
    int port = atoi(argv[1]);
    int socketfd;
    struct sockaddr_in si_me, si_other;
    char buffer [1024];
    socklen_t addr_size;
    socketfd = socket(AF_INET,SOCK_DGRAM,0); // define socket
    memset(&si_me,'\0',sizeof(si_me));
    si_me.sin_family=AF_INET;
    si_me.sin_port=htons(port);
    si_me.sin_addr.s_addr = inet_addr(argv[2]);

    bind(socketfd, (struct sockaddr*)  &si_me, sizeof(si_me));
    addr_size = sizeof(si_other);

    do{
        recvfrom(socketfd,buffer,1024,0,(struct sockaddr*)&si_other, &addr_size);
        printf("Data Recieved: %s \n",buffer);
        sendto(socketfd, buffer, 1024, 0, (struct sockaddr*)&si_other, sizeof(si_other));
    }while ( strcmp (buffer,"Q") !=0  );

    return 0;

}