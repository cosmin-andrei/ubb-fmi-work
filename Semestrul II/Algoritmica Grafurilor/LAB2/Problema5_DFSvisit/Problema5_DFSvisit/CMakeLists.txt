# CMakeList.txt : CMake project for Problema5_DFSvisit, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Problema5_DFSvisit "Problema5_DFSvisit.cpp" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Problema5_DFSvisit PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
