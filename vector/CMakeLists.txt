cmake_minimum_required(VERSION 3.10)

project(Vector)

set(CMAKE_CXX_STANDARD 17)

add_executable(MyVector
    headers/myvector.h
    cources/main.cpp
    headers/myvector.hpp
)