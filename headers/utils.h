#ifndef _UTIL_H_
#define _UTIL_H_


#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/algorithm/string.hpp>

#include <sstream>      
#include <iomanip>
#include <iostream>

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

#endif