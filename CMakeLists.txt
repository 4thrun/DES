cmake_minimum_required(VERSION 3.19)
project(DES)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(DES
        main.c src/mode.h src/utils.h src/utils.c src/DES.c src/DES.h src/mode.c)
