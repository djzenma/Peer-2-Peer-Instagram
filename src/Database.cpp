// #include "Database.h"

// Database::Database(std::string file_name){
//     db_file =file_name;
// }

// std::map<std::string,int> Database::getAllUsers(int image_id){
//     Json::Reader reader;
//     Json::Value obj;
//     std::ifstream ifs = std::ifstream(db_file, std::ifstream::binary);
//     reader.parse(ifs, obj); 

//     std::map<std::string, int> users_list; 
//     const Json::Value users = obj[std::to_string(image_id)+ ".jpg"];
//     for (auto const& user_name : users.getMemberNames()){
//         users_list[user_name]  = atoi(users[user_name].asString().c_str());
//         std::cout << user_name << " has " << users[user_name] << std::endl;
//     }
//     return users_list;
// } 

// int Database::getUser(int image_id, std::string user_name){
//     Json::Reader reader;
//     Json::Value obj;
//     std::ifstream ifs = std::ifstream(db_file, std::ifstream::binary);
//     reader.parse(ifs, obj); 
//     int view_count;
//     const Json::Value users = obj[std::to_string(image_id)+".jpg"];
//     for (auto const& id : users.getMemberNames()){
//         if(id == user_name){
//             view_count = atoi(users[user_name].asString().c_str());
//             std::cout << id << " has " << users[id] << std::endl;
//         }
//     }
//     return view_count;
// }
// bool Database::updateCount(int image_id, std::string user_name, int updated_count){
//     Json::Reader reader;
//     Json::Value obj;
//     std::ifstream ifs = std::ifstream(db_file, std::ifstream::binary);
//     reader.parse(ifs, obj); 
//     Json::Value users = obj[std::to_string(image_id)+".jpg"];
//     for (auto const& id : users.getMemberNames()){
//         if(id == user_name){
//             obj[std::to_string(image_id)+".jpg"][id] = Json::Value(updated_count);
//         }
//     }
//     Json::StyledStreamWriter styledStream;
//     std::ofstream ofs (db_file, std::ofstream::out);
//     styledStream.write(ofs, obj);
//     return true;
// }

// bool Database::insertUser(std::string image_id, std::tuple<std::string, int> userInfo ){


// }

// bool insertImage(std::string image_id){


// }

// Database::~Database(){

// }