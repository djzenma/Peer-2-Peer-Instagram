#ifndef DISTRIBUTEDC___ROBOT_H
#define DISTRIBUTEDC___ROBOT_H


#include <string>
#include "Peer.h"
#include "DoS.h"
#include "utils.h"

class Robot
{
private :
    const char* ip;
    const char* port;
    const char* dosIp;
    std::vector<std::string> IPs;

    Peer* peer;
    Communication* com;

public :
    ////Save db in map of maps ///// Save images in File Locally
    Robot ( const char* ip,  const char *dosIp); // create instance of peer, save ip and port
    void getIps(); //access DOS db and get all ips
    void connectToPeer(std::string ip); //  requestProfile FromPeer(Peer) & call getAllUsers (database) {create a function in Server}
    void createDb ();
    ~Robot () ;
};


#endif //DISTRIBUTEDC___ROBOT_H
