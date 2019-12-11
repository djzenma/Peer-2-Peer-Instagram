#ifndef STEGO_H
#define STEGO_H

#include <stdio.h>
#include <string>
#include <stdlib.h>
#include<iostream>
#include <fstream>
#include <sstream>

#include "Image.h"


#define COVER_PATH "../images/stego/cover.jpeg"
#define SECRET_TEXT_PATH "../images/stego/temp/secret.txt"

#define PASS_PHRASE "HEY"

#define DOCKER "docker run -it --rm -v $(pwd)/../images:/../images bartimar/steghide"


std::string stega_encode(std::string image_file,std::string secret_msg,std::string stego_image, bool include_cover);
std::string stega_decode(std::string stego_image, std::string extracted_image,  bool include_cover);
#endif