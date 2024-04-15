cmake_minimum_required(VERSION 3.10)

project(Vector)

set(CMAKE_CXX_STANDARD 20)

add_executable(MyVector
    headers/myvector.hpp
    cources/main.cpp
    headers/myvector.tpp
)