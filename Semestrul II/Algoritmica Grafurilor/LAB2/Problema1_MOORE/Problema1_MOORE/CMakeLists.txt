# CMakeList.txt : CMake project for Problema1_MOORE, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Problema1_MOORE "Problema1_MOORE.cpp" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Problema1_MOORE PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
