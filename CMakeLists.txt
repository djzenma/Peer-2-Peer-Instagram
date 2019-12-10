cmake_minimum_required(VERSION 3.9)
project(DistributedC__)

set(CMAKE_CXX_STANDARD 17)

#find_package(PkgConfig REQUIRED)
#pkg_check_modules(JSONCPP jsoncpp)
#link_libraries(${JSONCPP_LIBRARIES})
#include_directories(/usr/local/Cellar/jsoncpp/1.9.1/include/json)
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})
INCLUDE_DIRECTORIES(/usr/local/Cellar/jsoncpp/1.9.1/include)
LINK_DIRECTORIES(/usr/local/Cellar/jsoncpp/1.9.1/lib)

#get_target_property(JSON_INC_PATH jsoncpp_lib INTERFACE_INCLUDE_DIRECTORIES)
#include_directories(${JSON_INC_PATH})


add_executable(DistributedC__
        src/base64.cpp
        src/experiment.cpp

        headers/Message.h
        src/Message.cpp

        headers/RequestReply.h
        src/RequestReply.cpp

        headers/utils.h
        src/utils.cpp

        src/main.cpp

        headers/Peer.h
        src/Peer.cpp

        src/Stego.cpp
        headers/Stego.h

        src/DoS.cpp
        headers/DoS.h

        headers/Database.h
        src/Database.cpp

        headers/Image.h
        src/Image.cpp)

#target_link_libraries(DistributedC__ jsoncpp_lib)

#target_link_libraries(DistributedC__ ${JSONCPP_LIBRARIES})
target_link_libraries(DistributedC__ ${JSONCPP_LIBRARIES})