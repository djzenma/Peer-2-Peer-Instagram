#include "../headers/Message.h"
#include "../headers/utils.h"

Message::Message(): operation(0), rpc_id(0), message_size(0), message(""){

}
Message::Message(requestInfo req_info){
    message = req_info.p_message;
    message_size = req_info.p_message.length()+1;
    operation = req_info.operation;
    rpc_id = req_info.rpc_id;
    message_type = req_info.msg_type;
    // resource attributes
    image_id = req_info.image_id;
    storage_location = req_info.storage_location;
}

Message::Message(std::string & marshalled_base64){
    std::string decoded = decode64(marshalled_base64);
    std::string msg_decoded;
    deserialize(decoded);
}

// PRIVATE
void Message::deserialize(std::string decoded){

    std::string msg_decoded;

    message_type  = static_cast<MessageType>(decoded[0] - '0');
    message_size  = hex_to_int(decoded.substr(3, 16));
    operation = hex_to_int(decoded.substr(21, 8 ));
    rpc_id = hex_to_int(decoded.substr(31, 8 ));
    image_id = hex_to_int(decoded.substr(41, 8 ));
    storage_location = hex_to_int(decoded.substr( 49, decoded.substr(49).find(";")));
    msg_decoded = decoded.substr(49+storage_location.length());
    message = msg_decoded;
}

std::string Message::serialize(){
    // convert attributes to string
    std::string mtype = std::to_string(int(message_type));
    std::string size_str = int_to_hex(message_size);

    std::string op_str = int_to_hex(operation);
    std::string rpc_str = int_to_hex(rpc_id);
    std::string img_id = int_to_hex(image_id);

    // type: 1 byte | size: 2 bytes + 16 bytes  | operation : 2 bytes + 16 bytes
    // | rpc_id : 2 bytes + 16 bytes | img_id: 2 bytes + 8 bytes | storage_location | message

    std::string to_encode = mtype + size_str + op_str + rpc_str + img_id + storage_location + ";" + message;
    //std::cout << "encoded: " << to_encode << std::endl;
    //std::cout << "msg: " << message << std::endl;
    return to_encode;
}


std::string Message::marshal(){
    std::string to_encode = serialize();
    std::string encoded = encode64(to_encode);
    return encoded;
}
// getters
std::string Message::getMessage(){
    return message;
}
size_t Message::getMessageSize(){
    return message_size;
}
MessageType Message::getMessageType(){
    return message_type;
}
int Message::getOperation(){
    return operation;
}
int Message::getRPCId(){
    return rpc_id;
}

// setters
void Message::setMessage (std::string message, size_t message_size){
    this->message = message;
    this->message_size = message_size;
}

void Message::setMessageType (MessageType message_type){
    this->message_type = message_type;
}
void Message::setOperation(int operation){
    this->operation = operation;
}
void Message::setRPCId(int rpc_id){
    this->rpc_id = rpc_id;
}

int Message::getImageId(){
    return image_id;
}

std::string Message::getStorageLocation(){
    return storage_location;
}

Message::~Message(){

}

std::ostream& operator<< (std::ostream& stream, const Message& msg) {
    stream << "Type: " << msg.message_type
           << ", Size: " << msg.message_size
           << ", Operation: " << msg.operation
           << ", RPC_ID: " << msg.rpc_id
           << ", Message: " << msg.message
           << ", Image ID: " << msg.image_id
           << ", Storage Location: " << msg.storage_location << std::endl;
    return stream;
}