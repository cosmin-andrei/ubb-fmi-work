cmake_minimum_required(VERSION 3.10)
project(Tema3)

# Setează calea către Flex și Bison dacă sunt necesare
set(FLEX_EXECUTABLE "C:/GnuWin32/bin/flex.exe")
set(BISON_EXECUTABLE "C:/GnuWin32/bin/bison.exe")

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

# Adaugă directoarele de ieșire pentru fișierele generate
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Configurează scannerul Flex
flex_target(FlexScanner main.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c)

# Configurează parserul Bison
bison_target(BisonParser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.c)

# Creează executabilul, incluzând fișierele generate
add_executable(Tema3
        ${FLEX_FlexScanner_OUTPUTS}
        ${BISON_BisonParser_OUTPUTS}
        ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.h
)

# Link librăriile necesare (pe Windows, include ws2_32)
target_link_libraries(Tema3 ws2_32)
