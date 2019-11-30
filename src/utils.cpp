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

// Return IP from Address
std::string getIP(struct sockaddr_in addr) {
    return inet_ntoa(addr.sin_addr);
}