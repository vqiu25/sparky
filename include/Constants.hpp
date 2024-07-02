#pragma once

#include <string>

namespace Constants {
    // Screen dimensions
    constexpr int SCREEN_WIDTH = 800;
    constexpr int SCREEN_HEIGHT = 600;

    // Assets
    const std::string TITLE_LOGO_PATH = std::string(ASSET_PATH) + "startScene/sparkyLogo.png";
    const std::string SPACESHIP_PATH = std::string(ASSET_PATH) + "playScene/ship.png";
    const std::string LASER_PATH = std::string(ASSET_PATH) + "playScene/laser.png";
    const std::string BACKGROUND_PATH = std::string(ASSET_PATH) + "playScene/background.png";
    const std::string UFO_RED_PATH = std::string(ASSET_PATH) + "playScene/ufoRed.png";
    const std::string LASER_RED_PATH = std::string(ASSET_PATH) + "playScene/laserRed.png";
}