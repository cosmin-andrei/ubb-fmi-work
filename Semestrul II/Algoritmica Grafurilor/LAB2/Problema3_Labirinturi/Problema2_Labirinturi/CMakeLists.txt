# CMakeList.txt : CMake project for Problema2_Labirinturi, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Problema2_Labirinturi "Problema2_Labirinturi.cpp" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Problema2_Labirinturi PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
