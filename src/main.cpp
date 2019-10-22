#include<iostream>
#include <string>

#include "../headers/Client.h"
#include "../headers/Server.h"
#include "../headers/utils.h"

using namespace std;

int main(int argc,char **argv){  
      
    if(strcmp(argv[3], "client") == 0){ // equal doesn't work
        string server_ip = hostname_to_ip(argv[2]);
        new Client(argv[1], server_ip.c_str());
    }
    else{
        new Server(argv[1], argv[2]);
    }
    return 0;
}

