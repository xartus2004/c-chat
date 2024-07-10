cmake_minimum_required(VERSION 3.28)
project(untitled1 C)

set(CMAKE_C_STANDARD 17)

# Use absolute path or make sure the relative path is correct
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../socket-util socket-util-build)

add_executable(untitled1 main.c)

target_link_libraries(untitled1 PRIVATE socket_util)

# Use the include directory of the library, not the root directory
target_include_directories(untitled1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../socket-util)