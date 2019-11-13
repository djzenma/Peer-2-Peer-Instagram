#ifndef IMAGEMESSAGE_H
#define IMAGEMESSAGE_H

#include "Message.h"

struct requestInfo {
    int image_id;
    std::string storage_location;
    std::string p_message;           // msg buffer : contain text/image
    int operation;                  // operation id
    int rpc_id;                    // Unique request id
    MessageType msg_type;
};

class ImageMessage: public Message{
    int image_id;
    std::string storage_location;

public:
    ImageMessage(requestInfo req_info);
    ImageMessage(std::string & marshalled);

    std::string marshal();

    ~ImageMessage();

    friend std::ostream& operator<< (std::ostream& stream, const ImageMessage& msg);

};
#endif