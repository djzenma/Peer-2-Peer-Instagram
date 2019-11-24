#ifndef THREAD_H
#define THREAD_H

#include <iostream>
#include <thread>
#include "headers/Client.h"
#include "headers/Server.h"
#include "headers/Database.h"


using namespace std;

class Thread {

private:

    Database * db;

public:
    Thread(bool cli, bool first , int req , int image_id , bool parent, int por_num , string toConnectIp ,string toConnectPort, int num_views);
    ~Thread();
};
#endif
