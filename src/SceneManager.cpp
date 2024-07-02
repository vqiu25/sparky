#include "SceneManager.hpp"
#include "scenes/StartScene.hpp"
#include "scenes/PlayScene.hpp"
#include "scenes/EndScene.hpp"

SceneManager::SceneManager()
        : mCurrentScene{ScreenState::START}
        , mCurrentScenePtr{nullptr} {
    loadScene(this->mCurrentScene);
}

SceneManager::~SceneManager() {
    unloadScene();
}

void SceneManager::run() {
    while (!WindowShouldClose()) {
        update();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        draw();
        EndDrawing();
    }
}

void SceneManager::update() {
    if (this->mCurrentScenePtr) {
        this->mCurrentScenePtr->update();
    }
}

void SceneManager::draw() {
    if (this->mCurrentScenePtr) {
        this->mCurrentScenePtr->draw();
    }
}

void SceneManager::SetScreenState(ScreenState state) {
    if (this->mCurrentScene != state) {
        unloadScene();
        this->mCurrentScene = state;
        loadScene(state);
    }
}

void SceneManager::loadScene(ScreenState state) {
    switch (state) {
        case ScreenState::START:
            this->mCurrentScenePtr = new StartScene{this};
            break;
        case ScreenState::PLAY:
            this->mCurrentScenePtr = new PlayScene{this};
            break;
        case ScreenState::END:
            this->mCurrentScenePtr = new EndScene{this};
            break;
    }
}

void SceneManager::unloadScene() {
    delete this->mCurrentScenePtr;
    this->mCurrentScenePtr = nullptr;
}
