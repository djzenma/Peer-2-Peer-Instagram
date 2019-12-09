#ifndef IMAGE_H
#define IMAGE_H

#include <string.h>
#include "Message.h"
#include "Stego.h"


#define PATH "/Users/owner/CLionProjects/Distributed-Client/"


class Image{

    public:
        static Message buildImageMsg(int image_id, std::string owner_ip, std::string owner_name);
        static std::string encode(int image_id, std::string hidden_text);
        static std::string decode(int image_id);
        static int getViewCount(int image_id);
        static bool decrementViewCount(int image_id);
    
};
#endif