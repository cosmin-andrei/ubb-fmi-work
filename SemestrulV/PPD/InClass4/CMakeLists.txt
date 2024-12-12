cmake_minimum_required(VERSION 3.29)
project(InClass4)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

set(SOURCE_FILES main.cpp)
add_executable(InClass4 ${SOURCE_FILES})
