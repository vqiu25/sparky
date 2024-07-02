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
        src/SceneManager.cpp
        src/scenes/StartScene.cpp
        src/scenes/PlayScene.cpp
        src/scenes/EndScene.cpp
        src/entities/Spaceship.cpp
        src/entities/UFO.cpp
        src/entities/Laser.cpp)
# Assets
set(ASSET_PATH "${CMAKE_SOURCE_DIR}/assets")
add_definitions(-DASSET_PATH="${ASSET_PATH}/")

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
