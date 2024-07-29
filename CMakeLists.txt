cmake_minimum_required(VERSION 3.27)
project(DSA_SpotifyAPI)

set(CMAKE_CXX_STANDARD 11)

add_executable(DSA_SpotifyAPI main.cpp
        FrontEnd.cpp
        FrontEnd.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(c:/SFML/include/SFML)
target_link_libraries(DSA_SpotifyAPI sfml-system sfml-window sfml-graphics sfml-audio)