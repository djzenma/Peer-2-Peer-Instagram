cmake_minimum_required(VERSION 3.9)
project(DistributedC__)

set(CMAKE_CXX_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})
INCLUDE_DIRECTORIES(/usr/local/Cellar/jsoncpp/1.9.1/include)
LINK_DIRECTORIES(/usr/local/Cellar/jsoncpp/1.9.1/lib)

   add_executable(DistributedC__
           src/Client.cpp
           src/Message.cpp
           src/RequestReply.cpp
           src/Server.cpp
           src/utils.cpp
           src/main.cpp
           src/base64.cpp
           src/experiment.cpp
           src/Communication.cpp
           src/Thread.cpp
           src/DoS.cpp
           src/Peer.cpp
           /headers/Peer.h
           src/Database.cpp
           headers/Thread.h headers/utils.h src/Stego.cpp headers/Stego.h src/DoS.cpp headers/DoS.h headers/Communication.h headers/DoS.h headers/Database.h)

target_link_libraries(DistributedC__ ${JSONCPP_LIBRARIES})
