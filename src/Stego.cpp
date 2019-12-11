#include "../headers/Stego.h"



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
    //printf("Reading file %s, \n", file_name.c_str());
    //ifs = fopen(file_name.c_str(), "r");
    if (  (ifs = fopen(file_name.c_str(), "r")) ){
        while((len = static_cast<int>(fread(buf, 1, sizeof(buf) - 1, ifs))) > 0){
            //std::cout<<"Reading";
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
    std::string text_file = image_file + ".txt";
    std::ofstream outfile (text_file);
    outfile << secret_msg << std::endl;

    std::string str =  std::string(DOCKER) + " embed -ef ";
    std::string text_cmd =  std::string(DOCKER) + " embed -ef ";
    text_cmd = text_cmd  + text_file + " -cf " + image_file + " -sf " + stego_image;
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


std::string stega_decode(std::string stego_image, std::string  extracted_path, bool include_cover){
    std::string extracted_text = extracted_path + ".txt";

    std::string str = std::string(DOCKER) +" extract -sf ";
    str = str + stego_image + " -p " + "HEY" ;
    str = str + " -xf "  + extracted_path + " -f";

    std::cout << "Decoding Image file \n " << std::endl;
    exec(str);

    if(include_cover){
        str = std::string(DOCKER) + " extract -sf ";
        str = str  + extracted_path + " -p " + "HEY" ;
        str = str + " -xf "  + extracted_text + " -f";
        exec(str);
    }

    if(include_cover)
        return  read_file(std::string(extracted_text));
    else
        return read_file(std::string(extracted_path));
}