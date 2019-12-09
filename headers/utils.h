#ifndef _UTIL_H_
#define _UTIL_H_

#include <sstream>
#include <iomanip>
#include <iostream>
#include <netdb.h>
#include <sys/param.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "base64.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <string>
#include <vector>
#include <fstream>
#include "Message.h"


#define PATH "/home/manar/Documents/Uni/Fall2019/RRPSocket/Dist_Sockets/"

enum serviceOperations{
    SendImage = 0,
    UpdateViewCount = 1,
};


template< typename T >
std::string int_to_hex( T i ) {
    std::stringstream stream;
    stream << "0x"
           << std::setfill('0') << std::setw(sizeof(T)*2)
           << std::hex << i;
    return stream.str();
}

int hex_to_int(std::string  hex);

std::string encode64(const std::string &val);
std::string decode64(const std::string &val);

std::string hostname_to_ip(char * hostname);
void copyImage(std::string src, std::string dst);
std::string saveImage(std::string image, int image_id);

#endif
