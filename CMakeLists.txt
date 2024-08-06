cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(GatorPOP-main)


set(SFML_DIR "opt/homebrew/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS graphics window system REQUIRED)
add_executable(GatorPOP-main main.cpp
        FrontEnd.cpp
        FrontEnd.h
        HeapSort.cpp
        HeapSort.h
        extractSongs.h
        extractSongs.cpp)

target_link_libraries(GatorPOP-main sfml-system sfml-window sfml-graphics sfml-audio)