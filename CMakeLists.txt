cmake_minimum_required(VERSION 3.19)
project(DES)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

set(CMAKE_C_FLAGS "-std=c99")

add_executable(DES
        main.c src/utils.c src/DES.c src/mode.c)
