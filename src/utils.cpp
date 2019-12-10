#include <glob.h>
#include "../headers/utils.h"


// convert from integer to hexadecimal
int hex_to_int(std::string  hex){
    std::istringstream converter(hex);
    unsigned int value;
    converter >> std::hex >> value;
    return value;
}
std::string encode64(const std::string &val) {
    return base64_encode(reinterpret_cast<const unsigned char*>(val.c_str()), val.length());
}

std::string decode64(const std::string &val) {
    return base64_decode(val);
}

std::string hostname_to_ip(char * hostname){
    int i;
    struct hostent *he;
    struct in_addr **addr_list;

    if ((he = gethostbyname(hostname)) == NULL) {  // get the host info
        herror("gethostbyname");
        exit(1);
    }
    // print information about this host:
    printf("Official name is: %s\n", he->h_name);
    printf("    IP addresses: ");
    addr_list = (struct in_addr **)he->h_addr_list;
    for(i = 0; addr_list[i] != NULL; i++) {
        printf("%s ", inet_ntoa(*addr_list[i]));
    }
    printf("\n");
    std::string ip = inet_ntoa(*addr_list[0]);

    return ip;
}




// Return IP from Address
std::string getIP(struct sockaddr_in addr) {
    return inet_ntoa(addr.sin_addr);
}


bool is_number(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

void copyImage(std::string src, std::string dst){

    std::ifstream ifs (src, std::ifstream::in);
    std::ofstream outfile (dst, std::ofstream::out);
    // get size of file
    ifs.seekg (0,ifs.end);
    long size = ifs.tellg();
    ifs.seekg (0);

    // allocate memory for file content
    char* buffer = new char[size];

    // read content of infile
    ifs.read (buffer,size);

    // write to outfile
    outfile.write (buffer,size);

    // release dynamically-allocated memory
    delete[] buffer;

    outfile.close();
    ifs.close();
}

void saveImage(std::string image, int image_id, std::string directory){

    std::string temp_loc = "./../images/"+ directory + "/" + std::to_string(image_id) + ".jpg";

    std::ofstream outFile;
    outFile.open(temp_loc);
    outFile << image;
    outFile.close();
}



std::string generateRequestId(const std::string ip){
    static int req_num = 0;
    std::cout << ip + std::to_string(req_num) << std::endl;
    return ip + std::to_string(req_num++);
}


Message buildRequestMsg(DOS_OPERATIONS operation, const std::string senderIP, const int senderPort, const std::string msg){
    requestInfo reqinfo = {
            .image_id=0,
            .request_id= generateRequestId(senderIP),
            .p_message= msg,
            .operation = operation,
            .packet_index = 0,
            .IP= senderIP,
            .port = senderPort,
            .msg_type = Request
    };

    Message m = Message(reqinfo);
    return m;
}

Message buildReplyMsg(std::string requestId, const std::string msg, DOS_OPERATIONS operation, const std::string senderIP, const int senderPort){
    requestInfo reqinfo = {
            .image_id=0,
            .request_id= requestId,
            .p_message= msg,
            .operation = operation,
            .packet_index = 0,
            .IP= senderIP,
            .port = senderPort,
            .msg_type = Reply
    };

    Message m = Message(reqinfo);
    return m;
}


std::vector<std::string> globVector(const std::string& pattern){
    glob_t glob_result;
    glob(pattern.c_str(),GLOB_TILDE,NULL,&glob_result);
    std::vector<std::string> files;
    for(unsigned int i=0;i<glob_result.gl_pathc;++i){
        files.push_back(std::string(glob_result.gl_pathv[i]));
    }
    globfree(&glob_result);
    return files;
}