cmake_minimum_required(VERSION 3.6)
project(jackpot)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")

set(SOURCE_FILES
    controller.c
    controller.h main.c display.c display.h spinner.c spinner.h)

add_executable(jackpot ${SOURCE_FILES})