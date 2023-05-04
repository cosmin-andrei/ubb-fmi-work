# CMakeList.txt : CMake project for p1, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (p1 "p1.cpp" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET p1 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
