cmake_minimum_required(VERSION 3.10)
project(Tema3)

set(FLEX_EXECUTABLE "C:/Program Files (x86)/GnuWin32/bin/flex.exe")
find_package(FLEX REQUIRED)


flex_target(FlexScanner main.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c)
add_executable(Tema3 ${FLEX_FlexScanner_OUTPUTS})

target_link_libraries(Tema3 ws2_32)

