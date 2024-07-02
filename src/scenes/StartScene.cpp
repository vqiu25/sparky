#include "scenes/StartScene.hpp"
#include "SceneManager.hpp"

StartScene::StartScene(SceneManager* sceneManager)
    : Scene{sceneManager}
    , titleTexture{LoadTexture(Constants::TITLE_LOGO_PATH.c_str())} {}

void StartScene::update() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        mSceneManager->SetScreenState(PLAY);
    }
}

void StartScene::draw() {
    DrawTexture(titleTexture, (Constants::SCREEN_WIDTH - this->titleTexture.width) / 2, 120, WHITE);
    DrawText("[Press Anywhere to Start]", (Constants::SCREEN_WIDTH - MeasureText("[Press Anywhere to Start]", 25)) / 2, 340, 25, DARKGRAY);
}
