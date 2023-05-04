# CMakeList.txt : CMake project for LAB2, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (LAB2 LAB2.c  MyList.c MyList.h Tranzactie.c Tranzactie.h service.c service.h "CustomSort.c" "CustomSort.h" "my_utils.c" "my_utils.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET LAB2 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
