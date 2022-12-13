cmake_minimum_required(VERSION 3.24)
project(lab4)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)
include_directories(resources)

set(TINYXML_SOURCE D:/C/3sem_cpp/libs/tinyxml/tinyxmlparser.cpp D:/C/3sem_cpp/libs/tinyxml/tinyxmlerror.cpp D:/C/3sem_cpp/libs/tinyxml/tinyxml.cpp D:/C/3sem_cpp/libs/tinyxml/tinystr.cpp)

add_executable(lab4 main.cpp src/utils/observer/Observer.cpp src/utils/observer/Subject.cpp ${TINYXML_SOURCE})
add_executable(test test.cpp ${TINYXML_SOURCE})
add_executable(test1 test1.cpp ${TINYXML_SOURCE})

include_directories(D:/C/3sem_cpp/libs/tinyxml)

set(SFML_STATIC_LIBRARIES true)
set(SFML_DIR D:/C/3sem_cpp/libs/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

target_link_libraries(lab4 sfml-window sfml-audio sfml-system sfml-network sfml-graphics)
target_link_libraries(test sfml-system sfml-window sfml-graphics sfml-audio sfml-network )
target_link_libraries(test1 sfml-system sfml-window sfml-graphics sfml-audio sfml-network )
