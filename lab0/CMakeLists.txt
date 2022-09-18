cmake_minimum_required(VERSION 3.20)
project(lab0)

set(CMAKE_CXX_STANDARD 20)


add_subdirectory(builder)
add_subdirectory(application)

add_executable(test test.cpp)

