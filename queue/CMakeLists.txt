cmake_minimum_required(VERSION 3.10)

project(Queue)

set(CMAKE_CXX_STANDARD 20)

add_executable(
    Queue headers/queue.h 
    headers/queue.hpp 
    sources/main.cpp
)
