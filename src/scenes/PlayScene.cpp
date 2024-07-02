#include "scenes/PlayScene.hpp"
#include "SceneManager.hpp"

PlayScene::PlayScene(SceneManager* sceneManager)
        : Scene(sceneManager)
        , mPlayer{}
        , mBackgroundTexture{LoadTexture(Constants::BACKGROUND_PATH.c_str())}
        , mBackgroundOffset{0, 0} {}

PlayScene::~PlayScene() {
    UnloadTexture(mPlayer.getTexture());
    UnloadTexture(mPlayer.getLaserTexture());
    UnloadTexture(mBackgroundTexture);
}

void PlayScene::update() {
    mPlayer.update();

    mBackgroundOffset.x += mPlayer.getVelocity().x * 0.5f;
    mBackgroundOffset.y += mPlayer.getVelocity().y * 0.5f;

    // Wrap background offset
    if (mBackgroundOffset.x > mBackgroundTexture.width) mBackgroundOffset.x = 0;
    if (mBackgroundOffset.x < -mBackgroundTexture.width) mBackgroundOffset.x = mBackgroundTexture.width;
    if (mBackgroundOffset.y > mBackgroundTexture.height) mBackgroundOffset.y = 0;
    if (mBackgroundOffset.y < -mBackgroundTexture.height) mBackgroundOffset.y = mBackgroundTexture.height;
}

void PlayScene::draw() {
    for (int x = -1; x <= Constants::SCREEN_WIDTH / mBackgroundTexture.width; ++x) {
        for (int y = -1; y <= Constants::SCREEN_HEIGHT / mBackgroundTexture.height; ++y) {
            DrawTexture(mBackgroundTexture, mBackgroundOffset.x + x * mBackgroundTexture.width, mBackgroundOffset.y + y * mBackgroundTexture.height, WHITE);
        }
    }
    mPlayer.draw();
}
