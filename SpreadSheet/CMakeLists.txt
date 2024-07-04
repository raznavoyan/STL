cmake_minimum_required(VERSION 3.10)
project(SpreadSheet)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
# Define source and header directories
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/headers)

# Gather source files
set(SOURCES
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/spreadsheet.cpp
    ${SOURCE_DIR}/cell.cpp
)

include_directories(
    src
    headers
)

# Add the executable (use lowercase 'vector' for target name)
add_executable(spreadsheet ${SOURCES})