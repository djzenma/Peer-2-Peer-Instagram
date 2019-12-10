#ifndef IMAGE_H
#define IMAGE_H

#include <string.h>
#include "Message.h"
#include "Stego.h"


#define PATH "/home/manar/Documents/Uni/Fall2019/RRPSocket/Dist_Sockets/"


class Image{

    public:
        static Message buildImageMsg(int image_id, std::string hidden_text, std::string request_id);
        static Message buildProfileMsg(std::string request_id);
        static void reconstructSamplesMsg(Message& sampleMsg, std::string directory, int n);
        static void saveImage(std::string image, int image_id, std::string directory);

        static std::string readImage(std::string path);
        static std::string encode(int image_id, std::string hidden_text);
        static std::string decode(int image_id);
        static int getViewCount(int image_id);
        static bool decrementViewCount(int image_id);
    
};
#endif