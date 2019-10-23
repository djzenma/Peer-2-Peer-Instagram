#include "../headers/utils.h"

// convert from integer to hexadecimal
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
