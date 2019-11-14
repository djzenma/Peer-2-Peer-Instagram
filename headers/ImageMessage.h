#ifndef IMAGEMESSAGE_H
#define IMAGEMESSAGE_H

#include "Message.h"


class ImageMessage: public Message{
    int image_id;
    std::string storage_location;

public:
    ImageMessage();
    ImageMessage(requestInfo req_info);
    ImageMessage(std::string & marshalled);

    std::string marshal();
    // Getters
    int getImageId();
    std::string getStorageLocation();
    
    ~ImageMessage();

    friend std::ostream& operator<< (std::ostream& stream, const ImageMessage& msg);

};
#endif