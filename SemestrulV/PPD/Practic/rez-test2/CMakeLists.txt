cmake_minimum_required(VERSION 3.29)
project(rez_test2)

# Find MPI package (no need to manually set paths if MS MPI is installed)
find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})
add_executable(mpi2 main.cpp)

# Link MPI to the executables
target_link_libraries(mpi2 PRIVATE MPI::MPI_CXX)