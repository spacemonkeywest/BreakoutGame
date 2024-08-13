cmake_minimum_required(VERSION 3.10)
project(GameTwo)

set(CMAKE_CXX_STANDARD 17)

# Find SFML
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Add your executable
add_executable(run main.cpp)  # Replace main.cpp with your source files

# Link SFML libraries
target_link_libraries(run sfml-system sfml-window sfml-graphics)

