cmake_minimum_required(VERSION 3.29)
project(SSclient)

set(CMAKE_CXX_STANDARD 20)

add_executable(SSclient main.cpp
)

target_link_libraries(SSclient ws2_32)