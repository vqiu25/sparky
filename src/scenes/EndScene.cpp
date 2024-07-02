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
    DrawText("[Press Anywhere to Restart]", (Constants::SCREEN_WIDTH - MeasureText("[Press Anywhere to Restart]", 25)) / 2, 250, 25, DARKGRAY);
}
