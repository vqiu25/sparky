#include "SceneManager.hpp"
#include "Constants.hpp"

int main() {
    InitWindow(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, "Sparky");
    SetTargetFPS(60);

    SceneManager sceneManager;
    sceneManager.run();

    CloseWindow();
    return 0;
}
