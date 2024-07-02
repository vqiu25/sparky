#include "scenes/StartScene.hpp"
#include "SceneManager.hpp"

StartScene::StartScene(SceneManager* gameManager)
    : gameManager(gameManager) {}

void StartScene::update() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        gameManager->SetScreenState(PLAY);
    }
}

void StartScene::draw() {
    DrawText("Start Screen", 350, 280, 20, DARKGRAY);
    DrawText("Click to Play", 350, 310, 20, DARKGRAY);
}
