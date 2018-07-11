cmake_minimum_required(VERSION 3.10)
project(linuxReadSerial)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES src/main.cpp src/port.cpp)

add_executable(linuxReadSerial ${SOURCE_FILES})
