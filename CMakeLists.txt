cmake_minimum_required(VERSION 3.27)
project(Sparky VERSION 1.0)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# raylib
find_package(raylib 4.5.0 REQUIRED)

# Headers
include_directories(include)

# Source Files
add_executable(sparky
        src/main.cpp
        src/Game.cpp
        src/scenes/Screen.cpp
        src/scenes/StartScreen.cpp
        src/scenes/PlayScreen.cpp
        src/scenes/EndScreen.cpp)

# Link with raylib
target_link_libraries(sparky raylib)

# MacOS Configuration
if(APPLE)
    target_link_libraries(sparky
            "-framework CoreVideo"
            "-framework IOKit"
            "-framework Cocoa"
            "-framework GLUT"
            "-framework OpenGL")
endif()
