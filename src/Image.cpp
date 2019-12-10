#include "../headers/Image.h"


/*
    Builds a reply message with the stego image
*/
Message Image::buildImageMsg(int image_id, std::string hidden, std::string request_id){
   
    std::string path =   "../images/mine/" + std::to_string(image_id)+ ".jpg";
    std::string temp_path = "../images/stego/" + std::to_string(image_id)+ "_stego.jpg";

    std::string hidden_text = hidden;

    std::string stego_image = stega_encode(path, hidden_text, temp_path);
    
    requestInfo reqinfo = {
        .image_id=image_id,
        .request_id= request_id,
        .p_message= stego_image,
        .operation = SendImage,
        .packet_index = 0,
        .IP="",
        .port=0,
        .msg_type = Reply
    };

    Message msg = Message(reqinfo);
    return msg;
}
