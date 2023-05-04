# CMakeList.txt : CMake project for problema2, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (problema2 "problema2.cpp" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET problema2 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
