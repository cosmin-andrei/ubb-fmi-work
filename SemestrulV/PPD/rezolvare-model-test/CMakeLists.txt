cmake_minimum_required(VERSION 3.29)
project(rezolvare_model_test)

set(CMAKE_CXX_STANDARD 20)

# Find MPI package (no need to manually set paths if MS MPI is installed)
find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})
add_executable(mpi1 main.cpp)

# Link MPI to the executables
target_link_libraries(mpi1 PRIVATE MPI::MPI_CXX)