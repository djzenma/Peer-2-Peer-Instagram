#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstddef>
#include <string>
#include <iostream>
#include <cstring>

#include "utils.h"

enum MessageType {
    Request,
    Reply
};

struct requestInfo {
    int image_id;
    std::string request_id;
    std::string owner_ip;
    std::string owner_name;
    std::string p_message;           // msg buffer : contain text/image
    int operation;                  // operation id
    int rpc_id;                    // Unique request id
    MessageType msg_type;
};


class Message{

    private:
        MessageType message_type;
        std::string message;
        size_t message_size;
        int operation;
        int rpc_id;
        int image_id;
        std::string request_id;

    protected:
        std::string serialize();
        void deserialize(std::string marshalled);
    public:
        Message(std::string & marshalled_base64);
        Message(requestInfo req_info);
        Message();

        std::string marshal();

        // getters
        std::string getMessage();
        size_t getMessageSize();
        MessageType getMessageType();
        int getOperation();
        int getRPCId();
        int getImageId();
        std::string getRequestId();

        // setters
        void setOperation (int operation);
        void setMessage (std::string message, size_t message_size);
        void setMessageType (MessageType message_type);
        void setRPCId(int rpc_id);

        ~Message();

        friend std::ostream& operator<< (std::ostream& stream, const Message& msg);

};
#endif // MESSAGE_H
