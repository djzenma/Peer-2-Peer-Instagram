#include <fcntl.h>
#include <sys/stat.h>
#include "../headers/Image.h"

/*
    Builds a reply message with the stego image
*/


bool makeDirectory(std::string dir){
    struct stat info;
    int file_stat = stat(dir.c_str(), &info);
    if (file_stat != 0) {
        if (mkdir(dir.c_str(),S_IRWXU) != 0) {
            std::cout << "Not Able to Create Directory\n";
            return true;
        }
    }
    else if( info.st_mode & S_IFDIR ) {
        printf("%s is a directory\n", dir.c_str());
        return true;
    }
    else
        std::cout << "Error occured when creating directory\n";
    return false;
}

Message Image::buildImageMsg(int image_id, std::string hidden, std::string request_id) {

    std::string path = "../images/mine/profile/" + std::to_string(image_id) + ".jpg";



    std::string temp_path = "../images/stego/" + request_id + "_" + std::to_string(image_id) + "_stego.jpg";

    std::string hidden_text = hidden;

    std::string stego_image = stega_encode(path, hidden_text, temp_path, true);

    requestInfo reqinfo = {
            .image_id=image_id,
            .request_id= request_id,
            .p_message= stego_image,
            .operation = SendImage,
            .packet_index = 0,
            .IP="",
            .port=0,
            .sender_name ="",
            .msg_type = Reply
    };

    Message msg = Message(reqinfo);
    return msg;
}


Message Image::buildProfileMsg(std::string request_id) {
    std::string path = "../images/mine/samples/";
    std::string delimiter = "111110";
    std::string msg= "";

    for (int i = 0; i<6; i++) {
        std::string tempPath = path + std::to_string(i) + ".jpg";
        std::string image = Image::readImage(tempPath);
        msg += image + delimiter;

    }
    std::cout << msg << std::endl;

    requestInfo reqinfo = {
            .image_id=0,
            .request_id= request_id,
            .p_message= msg,
            .operation = SendProfile,
            .packet_index = 0,
            .IP="",
            .port=0,
            .sender_name="",
            .msg_type = Reply
    };

    Message m = Message(reqinfo);
    return m;
}


void Image::reconstructSamplesMsg(Message& sampleMsg, std::string directory, int n){
    static std::string delimiter = "111110";
    std::string samples = sampleMsg.getMessage();
    int imgId = sampleMsg.getImageId();

    size_t pos = 0;
    std::string token;
    while ((pos = samples.find(delimiter)) != std::string::npos) {
        token = samples.substr(0, pos);
        samples.erase(0, pos + delimiter.length());
        saveImage(token, imgId, directory );
        imgId++;
    }
}

std::string Image::readImage(std::string path) {
    std::ifstream fin(path, std::ios::in | std::ios::binary);
    std::ostringstream oss;
    oss << fin.rdbuf();
    std::string data(oss.str());
    return data;
}

void Image::saveImage(std::string image, int image_id, std::string directory){
    std::string path = "./../images/"+ directory + "/";
    std::string temp_loc = path + std::to_string(image_id) + ".jpg";

    struct stat info;
    int file_stat = stat(path.c_str(), &info);
    if (file_stat != 0) {
        if (mkdir(path.c_str(),S_IRWXU) != 0)
            std::cout << "Not Able to Create Directory\n";
    }
    else if( info.st_mode & S_IFDIR )
        printf( "%s is a directory\n", path.c_str());
    else
        std::cout << "Error occured when creating directory\n";

    std::string log = "\n\n\n\nImage directory: "+ temp_loc +"\n\n\n\n\n";
    std::perror(log.c_str());

    std::ofstream outFile;
    outFile.open(temp_loc);
    outFile << image;
    outFile.close();
}

//void Image::saveImage(std::string image, int image_id, std::string directory){
//
//    std::string temp_loc = "./../images/"+ directory + "/" + std::to_string(image_id) + ".jpg";
//
//    std::ofstream outFile;
//    outFile.open(temp_loc);
//    outFile << image;
//    outFile.close();
//}