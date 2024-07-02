#include "SceneManager.hpp"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Sparky");
    SetTargetFPS(60);

    SceneManager gameManager;
    gameManager.run();

    CloseWindow();
    return 0;
}
