#include "SceneManager.hpp"
#include "scenes/StartScene.hpp"
#include "scenes/PlayScene.hpp"
#include "scenes/EndScene.hpp"

SceneManager::SceneManager()
    : mCurrentScene{ScreenState::START}
    , mStartScene{new StartScene{this}}
    , mPlayScene{new PlayScene{this}}
    , mEndScene{new EndScene{this}} {}

SceneManager::~SceneManager() {
    delete mStartScene;
    delete mPlayScene;
    delete mEndScene;
    mStartScene = nullptr;
    mPlayScene = nullptr;
    mEndScene = nullptr;
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
    switch (mCurrentScene) {
        case START:
            mStartScene->update();
            break;
        case PLAY:
            mPlayScene->update();
            break;
        case END:
            mEndScene->update();
            break;
    }
}

void SceneManager::draw() {
    switch (mCurrentScene) {
        case START:
            mStartScene->draw();
            break;
        case PLAY:
            mPlayScene->draw();
            break;
        case END:
            mEndScene->draw();
            break;
    }
}

void SceneManager::SetScreenState(ScreenState state) {
    mCurrentScene = state;
}
