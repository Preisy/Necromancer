cmake_minimum_required(VERSION 3.20)
project(application)

set(CMAKE_CXX_STANDARD 20)

include_directories(model)
include_directories(view)
include_directories(controller)

include_directories(presentation)


set(SOURCES_API controller/MatrixController.cpp)
set(SOURCES_PR presentation/Dialog.cpp)

add_executable(startup startup.cpp ${SOURCES_API} ${SOURCES_PR})

include_directories(../builder)
target_link_libraries(startup builder)


