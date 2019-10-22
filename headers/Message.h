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
        void * message;
        size_t message_size;

    public:
        Message(void *p_message, size_t p_message_size);
        Message(char *marshalled_base64);
        char* marshal();
        // getters
        void *getMessage();
        size_t getMessageSize();
        MessageType getMessageType();
        // setters
        void setOperation (int _operation);
        void setMessage (void * message, size_t message_size);
        void setMessageType (MessageType message_type);
        ~Message();

        friend std::ostream& operator<< (std::ostream& stream, const Message& msg);

};
#endif // MESSAGE_H