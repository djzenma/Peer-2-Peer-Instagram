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
#include <algorithm>

#include "Message.h"


enum serviceOperations{
    SendImage = 0,
    UpdateViewCount = 1,
    SendProfile = 2,
    UpdateViewsRequestedImage = 3, // from server side
};

enum DOS_OPERATIONS {
    AUTH = 8,
    LOGIN = 9,
    SAMPLES_NUM = 10,
    PROFILE = 11,
    OK = 12,
    SAMPLES = 13,
    ROBOT = 14,
    P2P = 15,
    IP_MAP = 16,
    REFUSED = 17,
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

bool is_number(const std::string s);

std::string saveImg(std::string image, int image_id);

Message buildRequestMsg(DOS_OPERATIONS operation, const std::string senderIP, const int senderPort, const std::string msg);
Message buildReplyMsg(std::string requestId, const std::string msg, DOS_OPERATIONS operation, const std::string senderIP, const int senderPort);
std::string generateRequestId(const std::string ip);


std::vector<std::string> globVector(const std::string& pattern);
std::string getCurrentDir();


std::vector<std::string> parseHidden(std::string hidden_text);

#endif