cmake_minimum_required(VERSION 3.9)
project(DistributedC__)

set(CMAKE_CXX_STANDARD 11)

add_executable(DistributedC__ Client.h Server.h RequestReply.hpp main.cpp)