#ifndef DATABASE_H
#define DATABASE_H

#include <fstream>
#include <string>
#include <map>
#include <tuple>
#include <string>
#include <iostream>
#include <json/json.h>

class Database{

    private:
       std::string db_file;
    public:
        Database(std::string file_name);
        std::map<std::string,int> getAllUsers(int image_id);
        int getUser(int image_id, std::string user_name);  // returns view count
        bool insertUser(int image_id, std::tuple<std::string, int> userInfo );
        bool insertUser(std::tuple<std::string, std::string, std::string> userInfo);
        bool updateCount(int image_id, std::string user_name, int updated_count);
        ~Database();
};
#endif