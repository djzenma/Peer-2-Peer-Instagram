#ifndef DATABASE_H
#define DATABASE_H

#include <fstream>
#include <string>
#include <map>
#include <tuple>
#include <string>
#include <iostream>
//#include <json.h>

class Database{

    private:
       std::string db_file;
    public:
        Database(std::string file_name);
        std::map<std::string,int> getAllUsers(int image_id);
        int getUser(int image_id, std::string user_name);  // returns view count
        bool insertUser(std::string image_id, std::tuple<std::string, int> userInfo );
        bool insertImage(std::string image_id);
        bool updateCount(int image_id, std::string user_name, int updated_count);
        ~Database();
};
#endif
