#include "scenes/StartScene.hpp"
#include "SceneManager.hpp"

StartScene::StartScene(SceneManager* sceneManager)
    : Scene{sceneManager}
    , mTitleTexture{LoadTexture(Constants::TITLE_LOGO_PATH.c_str())} {}

void StartScene::update() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        this->mSceneManager->SetScreenState(PLAY);
    }
}

void StartScene::draw() {
    DrawTexture(this->mTitleTexture, (Constants::SCREEN_WIDTH - this->mTitleTexture.width) / 2, 120, WHITE);
    DrawText("[Press Anywhere to Start]", (Constants::SCREEN_WIDTH - MeasureText("[Press Anywhere to Start]", 25)) / 2, 340, 25, DARKGRAY);
}
