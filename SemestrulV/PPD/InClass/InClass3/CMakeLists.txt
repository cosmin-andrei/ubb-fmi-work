cmake_minimum_required(VERSION 3.29)
project(InClass3)

set(CMAKE_CXX_STANDARD 20)

find_package(MPI REQUIRED)

add_executable(InClass3 main.cpp)

target_link_libraries(InClass3 PRIVATE MPI::MPI_CXX)
