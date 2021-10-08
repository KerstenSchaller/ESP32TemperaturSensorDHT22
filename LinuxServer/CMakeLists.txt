cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 11)

project(IOTServer)

set(CMAKE_CXX_FLAGS "-fpermissive -std=c++0x")

add_subdirectory(IOTServer)
add_subdirectory(IOTTestClient)