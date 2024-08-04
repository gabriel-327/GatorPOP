cmake_minimum_required(VERSION 3.26.4)
project(GatorPOP)

set(CMAKE_CXX_STANDARD 11)

add_executable(GatorPOP main.cpp
        FrontEnd.cpp
        FrontEnd.h
        HeapSort.cpp
        HeapSort.h
        HashMap.h
        HashMap.cpp)

# SFML setup
set(SFML_DIR /Users/srividyadonthineni/Downloads/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(/Users/srividyadonthineni/Downloads/SFML/include)

target_link_libraries(GatorPOP sfml-system sfml-window sfml-graphics sfml-audio)
