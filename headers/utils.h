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


template< typename T >
std::string int_to_hex( T i ) {
  std::stringstream stream;
  stream << "0x" 
         << std::setfill('0') << std::setw(sizeof(T)*2) 
         << std::hex << i;
  return stream.str();
}


std::string encode64(const std::string &val);
std::string decode64(const std::string &val);

std::string hostname_to_ip(char * hostname);

#endif