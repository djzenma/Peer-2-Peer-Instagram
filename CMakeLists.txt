cmake_minimum_required(VERSION 3.9)
project(DistributedC__)

set(CMAKE_CXX_STANDARD 11)

add_executable(DistributedC__
        src/Client.cpp
        src/Message.cpp
        src/RequestReply.cpp
        src/Server.cpp
        src/utils.cpp
        src/main.cpp
        src/base64.cpp
        src/experiment.cpp
        headers/utils.h src/ImageMessage.cpp headers/ImageMessage.h src/Stego.cpp headers/Stego.h)

