#include "scenes/PlayScene.hpp"
#include "SceneManager.hpp"

PlayScene::PlayScene(SceneManager* sceneManager)
    : Scene(sceneManager)
    , framesCounter(0) {}

void PlayScene::update() {
    framesCounter++;
    if (framesCounter > 300) { // Example condition to end the game
        mSceneManager->SetScreenState(END);
    }
}

void PlayScene::draw() {
    DrawText("Play Screen", 350, 280, 20, DARKGRAY);
    DrawText(TextFormat("Frames: %i", framesCounter), 350, 310, 20, DARKGRAY);
}
