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

class Message{

private:
    MessageType message_type;
    std::string message;
    size_t message_size;
    int operation;
    int rpc_id;

protected:
    std::string serialize();
    void deserialize(std::string marshalled);
public:
    Message(std::string p_message, size_t p_message_size, int operation, int rpc_id);
    Message(std::string marshalled_base64);
    Message();

    std::string marshal();

    // getters
    std::string getMessage();
    size_t getMessageSize();
    MessageType getMessageType();
    int getOperation();
    int getRPCId();

    // setters
    void setOperation (int operation);
    void setMessage (std::string message, size_t message_size);
    void setMessageType (MessageType message_type);
    void setRPCId(int rpc_id);

    ~Message();

    friend std::ostream& operator<< (std::ostream& stream, const Message& msg);

};
#endif // MESSAGE_H