#include "scenes/StartScene.hpp"
#include "SceneManager.hpp"

StartScene::StartScene(SceneManager* sceneManager)
    : Scene{sceneManager} {}

void StartScene::update() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        mSceneManager->SetScreenState(PLAY);
    }
}

void StartScene::draw() {
    DrawText("Start Screen", 350, 280, 20, DARKGRAY);
    DrawText("Click to Play", 350, 310, 20, DARKGRAY);
}
