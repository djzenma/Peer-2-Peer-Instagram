#include "../headers/Stego.h"


#define COVER_PATH "../images/stego/cover.jpeg"
#define SECRET_TEXT_PATH "../images/stego/temp/secret.txt"
#define EXTRACTED_IMAGE_PATH "../images/stego/temp/extracted.jpeg"
#define EXTRACTED_TXT "../images/stego/temp/extracted.txt"

#define PASS_PHRASE "HEY"

#define DOCKER "docker run -it --rm -v $(pwd)/../images:/../images bartimar/steghide"


void exec(std::string str){
    const char *command = str.c_str(); 
    std::cout << "Executing : \n" << command << std::endl; 
    int txt_status = system(command); 
    if(txt_status){
        std::cout << "Error in Steghide. "<< std::endl; 
        exit(1);
    }
}

std::string read_file(std::string file_name){
    int len;
    char buf[1024];
    std::ostringstream oss; 
    FILE * ifs;
    printf("Reading file \n");
    //ifs = fopen(file_name.c_str(), "r");
    if (  (ifs = fopen(file_name.c_str(), "r")) ){
        while((len = fread(buf, 1, sizeof(buf) - 1, ifs)) > 0){
            oss.write(buf, len);
        }
        std::string data = oss.str(); // get string data out of stream
        return data;
    }
    else {
        printf("Error Opening File \n ");
        return "";
    };
}
std::string stega_encode(std::string image_file, std::string secret_msg, std::string stego_image, bool include_cover){
    // first: embed text inside image
    std::ofstream outfile (SECRET_TEXT_PATH);
    outfile << secret_msg << std::endl;

    std::string str =  std::string(DOCKER) + " embed -ef ";
    std::string text_cmd =  std::string(DOCKER) + " embed -ef ";
    text_cmd = text_cmd  + SECRET_TEXT_PATH + " -cf " + image_file + " -sf " + stego_image;
    text_cmd = text_cmd + " -p " + PASS_PHRASE + " -f";
    
    // encode secret msg inside image 
    exec(text_cmd);

    if (include_cover){
        // steghid shell invocation
        // steghid embed -ef <text file to embed> -cf <cover image> -sf < output image> -p <encryption password>
        str = str + stego_image + " -cf "  + COVER_PATH + " -sf " + stego_image;
        str = str + " -p " + PASS_PHRASE + " -f";

        exec(str);
    }

    return read_file(stego_image);  // return output stego image
}
std::string stega_decode(std::string stego_image){
    std::string str = std::string(DOCKER) +" extract -sf ";
    str = str + stego_image + " -p " + "HEY" ;
    str = str + " -xf "  + EXTRACTED_IMAGE_PATH + " -f";
    
    std::cout << "Decoding Image file \n " << std::endl; 
    exec(str);
   
    str = "steghide extract -sf "; 
    str = str  + EXTRACTED_IMAGE_PATH + " -p " + "HEY" ;
    str = str + " -xf "  + EXTRACTED_TXT + " -f";
    
    exec(str);
    
    return read_file(std::string(PATH) + std::string(EXTRACTED_TXT));
}
