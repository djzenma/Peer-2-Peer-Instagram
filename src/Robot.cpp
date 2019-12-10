
#include "../headers/Robot.h"


Robot::Robot(const char *ip,  const char * dosIp) {
    this->ip = ip;
    this->port = port;
    this->dosIp = dosIp;
    com = new Communication();
    peer = new Peer(ip, "Robot", dosIp);
}


void Robot::getIps() {
    char* res = com->comMsg(dosIp, DB_PORT, "robot", SEND_RECEIVE);
    if (is_number(res)) {
        std::cout<<"Robot: Receiving DB from DoS with size "<<res<<"...\n";
        for(int i = 0; i< std::stoi(res); i++) {
            char * ipEntry = com->comMsg(dosIp, DB_PORT, "", RECEIVE);
            IPs.push_back(ipEntry);
        }

    }
}
void Robot::createDb ()
{
    for (int i=0 ;i<IPs.size() ;i++) //for every peer in network
    {
        std::string ip = IPs.at(i) ;
        connectToPeer(ip);
    }
}
void Robot::connectToPeer(std::string ip) {
    peer->requestProfileFrom(ip, true); //get all images
    peer->getDB (const_cast<char *>(ip.c_str())); //  get user db

}

Robot::~Robot() {

}

