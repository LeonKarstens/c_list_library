cmake_minimum_required(VERSION 3.14)
project(node C)

set(CMAKE_C_STANDARD 99)

add_executable(node main.c node.h)