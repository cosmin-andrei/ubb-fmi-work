cmake_minimum_required(VERSION 3.20)
project(Translator)

set(CMAKE_CXX_STANDARD 17)

# Definirea cailor
set(SRC_DIR ${CMAKE_SOURCE_DIR})
set(BUILD_DIR ${CMAKE_BINARY_DIR})

# Regenerare fișiere din analizator.l și analizator.y
add_custom_command(
        OUTPUT ${BUILD_DIR}/lex.yy.c ${BUILD_DIR}/analizator.tab.c ${BUILD_DIR}/analizator.tab.h
        COMMAND flex -o ${BUILD_DIR}/lex.yy.c ${SRC_DIR}/analizator.l
        COMMAND bison -d -o ${BUILD_DIR}/analizator.tab.c ${SRC_DIR}/analizator.y
        DEPENDS ${SRC_DIR}/analizator.l ${SRC_DIR}/analizator.y
)

# Compilarea executabilului
add_executable(translator
        ${BUILD_DIR}/lex.yy.c
        ${BUILD_DIR}/analizator.tab.c
)

# Comenzi pentru asamblare și linkeditare
add_custom_target(assemble_asm ALL
        COMMAND nasm -f obj ${BUILD_DIR}/asmCode.asm
        COMMAND alink.exe -oPE -subsys console -entry start ${BUILD_DIR}/asmCode.obj
        DEPENDS ${BUILD_DIR}/asmCode.asm
)
