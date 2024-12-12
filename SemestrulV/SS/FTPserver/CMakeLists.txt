cmake_minimum_required(VERSION 3.29)
project(FTPserver)

set(CMAKE_CXX_STANDARD 20)

add_executable(FTPserver main.cpp
        server.cpp
        server.h
        handle_cmd.cpp
        handle_cmd.h
)

if(WIN32)
    target_link_libraries(FTPserver PRIVATE ws2_32)
endif()