cmake_minimum_required(VERSION 3.20)

project(builder)

set(SOURCES Builder.cpp)

add_library(${PROJECT_NAME} ${SOURCES})