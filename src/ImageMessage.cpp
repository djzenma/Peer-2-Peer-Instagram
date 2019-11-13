#include "../headers/ImageMessage.h"


ImageMessage::ImageMessage(requestInfo req_info)
        :Message(req_info.p_message, req_info.p_message.length()+1, req_info.operation, req_info.rpc_id){

    Message::setMessageType(req_info.msg_type);

    image_id = req_info.image_id;
    storage_location = req_info.storage_location;
};

ImageMessage::ImageMessage(std::string & marshalled_base64){
    std::string decoded = decode64(marshalled_base64);
    Message::deserialize(decoded);
    int image_id_pos = decoded.substr(39).find("0x");
    image_id = hex_to_int(decoded.substr(image_id_pos+2, 8));
    storage_location = decoded.substr(image_id_pos+39+10);
}

std::string ImageMessage::marshal(){
    std::string msg_serialized = Message::serialize();
    std::string img_info_serialized = int_to_hex(image_id) + storage_location;
    std::string to_encode = msg_serialized + img_info_serialized;
    std::string encoded = encode64(to_encode);
    return encoded;
}

ImageMessage::~ImageMessage(){

}

std::ostream& operator<< (std::ostream& stream, const ImageMessage& msg) {
    const Message & m(msg);
    stream << m
           << ", Image ID: " << msg.image_id
           << ", Storage Location: " << msg.storage_location << std::endl;
    return stream;
}