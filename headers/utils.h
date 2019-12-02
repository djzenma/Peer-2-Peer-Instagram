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


enum serviceOperations{
    SendImage = 0,
    GrantAccess = 1,
    DecrementView = 2,
    SendSample = 3,
    SendImages = 4,
    ViewAccess = 5,
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
// Base 64
std::string encode64(const std::string &val);
std::string decode64(const std::string &val);

std::string hostname_to_ip(char * hostname);
void copyImage(std::string src, std::string dst);
// Return IP from Address
std::string getIP(struct sockaddr_in addr);
int getPort(sockaddr_in sa);

#endif
