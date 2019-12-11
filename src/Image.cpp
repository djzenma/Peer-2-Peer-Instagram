//
// Created by Mazen on 07.12.19.
//

#include <json/value.h>
#include <json/json.h>
#include "../headers/Image.h"
#include <stdio.h>
#include "../headers/utils.h"


/*
    Builds a reply message with the stego image
*/

Message Image::buildImageMsg(int image_id, std::string hidden, std::string request_id, const int senderPort) {

    std::string path = "../images/mine/" + std::to_string(image_id) + ".jpg";
    std::string temp_path = "../images/stego/" + std::to_string(image_id) + "_stego.jpg";

    std::string hidden_text = hidden;

    std::string stego_image = stega_encode(path, hidden_text, temp_path, true);

    requestInfo reqinfo = {
            .image_id=image_id,
            .request_id= request_id,
            .p_message= stego_image,
            .operation = SendImage,
            .packet_index = 0,
            .IP="",
            .port= senderPort,
            .msg_type = Reply
    };

    Message msg = Message(reqinfo);
    return msg;
}


/*
    Peer Builds a Samples Msg
*/
Message Image::buildSamplesMsg(bool fromDoS, DOS_OPERATIONS operation, int images_id[], const std::string ip, const int senderPort, std::string ownerName, int n){
    std::string request_id = generateRequestId(ip);

    std::string delimiter = "111110";
    std::string msg= "";
    std::string path;

    if(fromDoS) {
        std::vector<std::string> usersDirs = globVector("../images/users/*");
        for ( std::string &user : usersDirs) {
            // Delimit by Slash
            std::string delimiter = "/";
            size_t pos = 0;
            while ((pos = user.find(delimiter)) != std::string::npos) {
                user.substr(0, pos);
                user.erase(0, pos + delimiter.length());
            }
            if(user != ownerName) {
                std::cout<<"\n\nowner:"<<user<<" "<<ownerName<<"\n\n";
                path = "../images/users/" + user + "/";
                for (int i = 0; i < n; i++) {
                    std::string imgPath = path + std::to_string(images_id[i]) + ".jpg";
                    //std::string image = Image::readImage(imgPath);

                    // Read Json of the user
                    Json::Value userProfile;
                    std::ifstream userJson(path+"/profile.json", std::ifstream::binary);
                    userJson >> userProfile;
                    Profile profile;
                    profile.user = userProfile[user]["username"].asString();
                    profile.ip = userProfile[user]["ip"].asString();

                    std::string hiddenTxt = profile.user + "/" + profile.ip;
                    std::string encodedImage = stega_encode(imgPath, hiddenTxt, "../images/stego/" + std::to_string(images_id[i]) + ".jpg", false);
                    msg += encodedImage + delimiter;
                }
            }
        }
    }
    else {
        path = "../images/mine/samples/";
        for (int i = 0; i < n; i++) {
            std::string tempPath = path + std::to_string(images_id[i]) + ".jpg";
            std::string image = Image::readImage(tempPath);
            std::string hiddenTxt = ownerName + "/"+ ip;
            std::string encodedImage = stega_encode(tempPath, hiddenTxt, "../images/stego/" + std::to_string(images_id[i]) + ".jpg", false);
            msg += encodedImage + delimiter;
        }
    }

    requestInfo reqinfo = {
            .image_id=images_id[0],
            .request_id= request_id,
            .p_message= msg,
            .operation = operation,
            .packet_index = 0,
            .IP=ip,
            .port = senderPort,
            .msg_type = Request
    };

    Message m = Message(reqinfo);
    return m;
}

/*
    Reconstruct the Samples Msg
*/
Profile Image::reconstructSamplesMsg(bool isDoS, Message& sampleMsg, std::string directory){
    static std::string delimiter = "111110";
    std::string samples = sampleMsg.getMessage();
    int imgId = sampleMsg.getImageId();
    Profile profile;

    size_t pos = 0;
    std::string imgToken;
    while ((pos = samples.find(delimiter)) != std::string::npos) {
        imgToken = samples.substr(0, pos);
        samples.erase(0, pos + delimiter.length());
        if(isDoS) {
            // Get owner Name
            int r = rand()%10000;
            saveImage(imgToken, imgId, "temp/" + std::to_string(r));    // save the image in a dummy dir
            std::string hidden = stega_decode("./../images/temp/" + std::to_string(r) + "/" + std::to_string(imgId) + ".jpg", "./../images/temp/" + std::to_string(r) + "/" + std::to_string(imgId) + ".txt", false);    // decode the img from the dummy dir
            std::string hiddenDelimiter = "/";
            size_t pos = 0;
            std::string hiddenToken;
            while ((pos = hidden.find(hiddenDelimiter)) != std::string::npos) {
                hiddenToken = hidden.substr(0, pos);
                profile.user= hiddenToken;
                hiddenToken.erase(0, pos + hiddenDelimiter.length());
            }
            profile.ip = hidden;

            saveImage(imgToken, imgId, "users/"+ profile.user); // save the img to the corresponding user
        }
        else
            saveImage(imgToken, imgId, directory);
        imgId++;
    }

    return profile;
}


std::string Image::readImage(std::string path) {
    std::ifstream fin(path, std::ios::in | std::ios::binary);
    std::ostringstream oss;
    oss << fin.rdbuf();
    std::string data(oss.str());
    return data;
}


Message Image::buildProfileMsg(std::string request_id, const int senderPort) {
    std::string path = "../images/mine/profile/";
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
            .port= senderPort,
            .msg_type = Reply
    };

    Message m = Message(reqinfo);
    return m;
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


    std::ofstream outFile;
    outFile.open(temp_loc);
    outFile << image;
    outFile.close();
}