#include "scenes/EndScene.hpp"
#include "SceneManager.hpp"

EndScene::EndScene(SceneManager* sceneManager)
    : Scene(sceneManager) {}

void EndScene::update() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        mSceneManager->SetScreenState(START);
    }
}

void EndScene::draw() {
    DrawText("End Screen", 350, 280, 20, DARKGRAY);
    DrawText("Click to Restart", 350, 310, 20, DARKGRAY);
}
