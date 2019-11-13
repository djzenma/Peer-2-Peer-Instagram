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

struct credentials{
    std::string username;
    std::string passwrod;
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

// Steganography
std::string stegoEncode(std::string file_name, credentials owner,
                        std::vector<std::string> users, std::vector<int> num_grants);

std::string stegoDecode();

std::string hostname_to_ip(char * hostname);

#endif