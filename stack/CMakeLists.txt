cmake_minimum_required(VERSION 3.10)

project(Stack)

set(CMAKE_CXX_STANDARD 20)

add_executable(Stack 
    headers/stack.h
    headers/stack.cpp
    sources/main.cpp
)
