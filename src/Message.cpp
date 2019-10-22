#include "../headers/Message.h"

Message::Message(void *p_message, size_t p_message_size){
    message = (char *) malloc(sizeof(p_message));
    std::strcpy((char *)message, (char *)p_message);
    message_size = p_message_size;
}
Message::Message(char * marshalled_base64){
    std::string decoded = decode64(std::string(marshalled_base64));
    message_type  = static_cast<MessageType>(decoded[0] - '0');
    message_size  = atoi(decoded.substr(3, 16).c_str());
    std::string msg_decoded = decoded.substr(19);

    message =  (char *) malloc(sizeof(msg_decoded));
    std::strcpy((char *)message, msg_decoded.c_str());
}
char* Message::marshal(){
    // convert attributes to string
    char * marshalled;
    std::string mtype = std::to_string(int(message_type));
    std::string size_str = int_to_hex(message_size);
    
    // type: 1 byte | size: 2 bytes + 16 bytes   | message
    std::string to_encode = mtype + size_str + std::string((char *) message);
    std::string encoded = encode64(to_encode);
   
    marshalled =  (char *) malloc(sizeof(encoded));
    std::strcpy(marshalled, encoded.c_str());

    return marshalled;
}
// getters
void* Message::getMessage(){
    return message;
}
size_t Message::getMessageSize(){
    return message_size;
}
MessageType Message::getMessageType(){
    return message_type;
}

// setters
void Message::setMessage (void *message, size_t message_size){
    this->message = message;
    this->message_size = message_size;
}

void Message::setMessageType (MessageType message_type){
    this->message_type = message_type;
}

Message::~Message(){
    free(message);
}

std::ostream& operator<< (std::ostream& stream, const Message& msg) {
    stream << "Type: " << msg.message_type
           << ", Size: " << msg.message_size
           << ", Message: " << (char *) msg.message << std::endl;
    return stream; 
}
