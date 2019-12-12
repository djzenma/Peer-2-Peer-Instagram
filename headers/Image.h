#ifndef IMAGE_H
#define IMAGE_H

#include <string.h>
#include "Message.h"
#include "Stego.h"
#include "utils.h"
#include "DoS.h"

#define PATH "/home/manar/Documents/Uni/Fall2019/RRPSocket/Dist_Sockets/"


class Image{

public:
    static Message buildImageMsg(int image_id, std::string hidden_text, std::string request_id, const int senderPort);
    static Message buildSamplesMsg(bool fromDoS, DOS_OPERATIONS operation, int images_id[], const std::string ip, const int senderPort, std::string ownerName, int n);
    static struct Profile reconstructSamplesMsg(bool isDoS, Message& sampleMsg, std::string directory);

    static std::string readImage(std::string path);
    static void saveImage(std::string image, int image_id, std::string directory);





    static Message buildImageMsg(int image_id, std::string hidden_text, std::string request_id);
    static Message buildProfileMsg(std::string request_id);
    static void reconstructSamplesMsg(Message& sampleMsg, std::string directory, int n);
};
#endif
