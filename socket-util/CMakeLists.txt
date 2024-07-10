cmake_minimum_required(VERSION 3.28)
project(socket_util C)

set(CMAKE_C_STANDARD 17)

add_library(socket_util STATIC socketutil.c socketutil.h)

target_include_directories(socket_util PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})