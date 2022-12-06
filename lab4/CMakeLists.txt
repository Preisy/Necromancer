cmake_minimum_required(VERSION 3.24)
project(lab4)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)
add_executable(lab4 main.cpp)

set(SFML_DIR D:/C/3sem_cpp/libs/SFML/lib/cmake/SFML)
find_package(SFML 2.5 COMPONENTS system window graphics audio network REQUIRED)
target_link_libraries(lab4 sfml-window sfml-audio sfml-system sfml-network sfml-graphics)
