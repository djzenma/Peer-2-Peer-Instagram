#ifndef STEGO_H
#define STEGO_H

#include <stdio.h>
#include <string>
#include <stdlib.h>
#include<iostream>
#include <fstream>
#include <sstream>

std::string stega_encode(std::string image_file,std::string secret_msg,std::string stego_image);
std::string stega_decode(std::string stego_image);

#endif