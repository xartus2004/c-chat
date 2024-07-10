cmake_minimum_required(VERSION 3.28)
project(socket_server C)

set(CMAKE_C_STANDARD 17)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../socket-util socket-util-build)

add_executable(socket_server main.c)

target_link_libraries(socket_server PRIVATE socket_util)

# Use the include directory of the library, not the root directory
target_include_directories(socket_server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../socket-util)