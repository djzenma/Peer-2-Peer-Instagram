#include<iostream>
#include <string>

#include "../headers/Client.h"
#include "../headers/Server.h"

using namespace std;

int main(int argc,char **argv){
    if(argv[3] == "client")
        new Client(argv[1], argv[2]);
    else
        new Server(argv[1], argv[2]);
    return 0;
}

