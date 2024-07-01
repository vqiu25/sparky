cmake_minimum_required(VERSION 3.27)
project(Sparky VERSION 1.0)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# raylib
find_package(raylib 4.5.0 REQUIRED)

# Header Files
include_directories(${RAYLIB_INCLUDE_DIRS})
include_directories(include)

# Source Files
add_executable(sparky
        src/main.cpp
        src/Game.cpp)

# Link with raylib
target_link_libraries(sparky ${RAYLIB_LIBRARIES})