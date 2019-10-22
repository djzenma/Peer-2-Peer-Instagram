#include "utils.h"

// convert from integer to hexadecimal
std::string encode64(const std::string &val) {
    return base64_encode(reinterpret_cast<const unsigned char*>(val.c_str()), val.length());
}

std::string decode64(const std::string &val) {
    return base64_decode(val);
}

std::string hostname_to_ip(char * hostname){
    hostent * record = gethostbyname(hostname);
	if(record == NULL)
	{
		printf("%s is unavailable\n",hostname );
		exit(1);
	}
	in_addr * address = (in_addr * )record->h_addr;
	std::string hostIP = inet_ntoa(* address);
    return hostIP;    
}
