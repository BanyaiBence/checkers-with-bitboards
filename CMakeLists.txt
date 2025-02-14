cmake_minimum_required(VERSION 3.30)
project(BitboardCheckers C)

set(CMAKE_C_STANDARD 11)

add_executable(BitboardCheckers main.c
        board.c
        board.h
        macros.h
)
