cmake_minimum_required(VERSION 3.6)
project(jackpot)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -lrt -lpthread")

set(SOURCE_FILES main.c display.c display.h spinner.c spinner.h threads.c threads.h)

add_executable(jackpot ${SOURCE_FILES})