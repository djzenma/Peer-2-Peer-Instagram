
#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstddef>
#include <string>
#include <iostream>
#include <cstring>

#include "utils.h"


enum MessageType {
    Request,
    Reply,
    ACK,
    ACKReply
};

struct requestInfo {
    int image_id;
    std::string request_id;
    std::string p_message;           // msg buffer : contain text/image
    int operation;                  // operation id
    int packet_index;                    // Unique request id
    std::string IP;
    int port;
    MessageType msg_type;
};


class Message{

private:
    MessageType message_type;
    std::string message;
    size_t message_size;
    int operation;
    int packet_index;
    int total_packets;

    int image_id;
    std::string request_id;
    std::string IP;
    int port;

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
    int getPacketIndex();
    int getTotalPackets();

    int getImageId();
    std::string getIP();
    std::string getRequestId();
    int getPort();

    // setters
    void setOperation (int operation);
    void setMessage (std::string message, size_t message_size);
    void setMessageType (MessageType message_type);
    void setPacketIndex(int packet_index);
    void setTotalPacket(int tot_packets);
    void setRequestId(std::string rq_id);
    void setIP (std::string ip);
    void setPort(int port);
    void setMessageSize(size_t message_size);

    // BUILD ACK msg
    static Message buildAckMsg(Message & m);

    ~Message();

    friend std::ostream& operator<< (std::ostream& stream, const Message& msg);

};
#endif // MESSAGE_H