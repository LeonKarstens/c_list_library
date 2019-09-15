cmake_minimum_required(VERSION 3.14)
project(node C)

set(CMAKE_C_STANDARD 99)

add_library(nodeLib node.c node.h)
add_executable(nodeTest main.c)

target_link_libraries(nodeTest nodeLib)