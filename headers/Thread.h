#ifndef THREAD_H
#define THREAD_H

#include <iostream>
#include <thread>
#include "../headers/Client.h"
#include "../headers/Server.h"


using namespace std;

class Thread {

private:



public:
    Thread(bool cli, bool first , int req , int image_id , string serverName, int por_num , string toConnectIp ,string toConnectPort );
    ~Thread();
};
#endif
