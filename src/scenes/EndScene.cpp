#include "scenes/EndScene.hpp"
#include "SceneManager.hpp"

EndScene::EndScene(SceneManager* gameManager) : gameManager(gameManager) {}

void EndScene::update() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        gameManager->SetScreenState(START);
    }
}

void EndScene::draw() {
    DrawText("End Screen", 350, 280, 20, DARKGRAY);
    DrawText("Click to Restart", 350, 310, 20, DARKGRAY);
}
