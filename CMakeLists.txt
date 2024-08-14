cmake_minimum_required(VERSION 3.10)
project(GameTwo)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

add_executable(run main.cpp)

target_link_libraries(run sfml-system sfml-window sfml-graphics)

