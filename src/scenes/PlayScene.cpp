#include "scenes/PlayScene.hpp"
#include "SceneManager.hpp"
#include "Constants.hpp"

PlayScene::PlayScene(SceneManager* sceneManager)
        : Scene(sceneManager)
        , mPlayer{}
        , mBackgroundTexture{LoadTexture(Constants::BACKGROUND_PATH.c_str())}
        , mBackgroundOffset{0, 0}
        , mUfos{}
        , mSpawnTimer{0} {
    spawnUFOs(3);
}

PlayScene::~PlayScene() {
    UnloadTexture(mPlayer.getTexture());
    UnloadTexture(mPlayer.getLaserTexture());
    UnloadTexture(mBackgroundTexture);

    for (auto& ufo : this->mUfos) {
        UnloadTexture(ufo.getTexture());
        UnloadTexture(ufo.getLaserTexture());
    }
}

void PlayScene::update() {
    mPlayer.update();

    for (auto& ufo : mUfos) {
        ufo.update(mPlayer.getPosition());
        if (GetRandomValue(0, 100) < 2) {
            ufo.shoot(mPlayer.getPosition());
        }
    }

    mBackgroundOffset.x += mPlayer.getVelocity().x * 0.5f;
    mBackgroundOffset.y += mPlayer.getVelocity().y * 0.5f;

    // Wrap background offset
    if (mBackgroundOffset.x > mBackgroundTexture.width) mBackgroundOffset.x = 0;
    if (mBackgroundOffset.x < -mBackgroundTexture.width) mBackgroundOffset.x = mBackgroundTexture.width;
    if (mBackgroundOffset.y > mBackgroundTexture.height) mBackgroundOffset.y = 0;
    if (mBackgroundOffset.y < -mBackgroundTexture.height) mBackgroundOffset.y = mBackgroundTexture.height;

    // Collision detection between lasers and UFOs
    for (auto& laser : mPlayer.getLasers()) {
        for (auto& ufo : mUfos) {
            if (CheckCollisionCircles(laser.getPosition(), 3, ufo.getPosition(), ufo.getTexture().width / 2)) {
                ufo.takeDamage(10);
                laser.setActive(false);
            }
        }
    }

    // Remove dead UFOs
    mUfos.erase(std::remove_if(mUfos.begin(), mUfos.end(), [](UFO& u) { return u.getHealth() <= 0; }), mUfos.end());

    // Spawn new UFOs over time
    mSpawnTimer++;
    if (mSpawnTimer > 600) {  // Every 600 frames (10 seconds at 60 FPS)
        spawnUFO();
        mSpawnTimer = 0;
    }
}

void PlayScene::draw() {
    for (int x = -1; x <= Constants::SCREEN_WIDTH / mBackgroundTexture.width; ++x) {
        for (int y = -1; y <= Constants::SCREEN_HEIGHT / mBackgroundTexture.height; ++y) {
            DrawTexture(mBackgroundTexture, mBackgroundOffset.x + x * mBackgroundTexture.width, mBackgroundOffset.y + y * mBackgroundTexture.height, WHITE);
        }
    }
    mPlayer.draw();

    for (auto& ufo : mUfos) {
        ufo.draw();
    }
}

void PlayScene::spawnUFOs(int count) {
    Texture2D ufoTexture = LoadTexture(Constants::UFO_RED_PATH.c_str());
    for (int i = 0; i < count; ++i) {
        Vector2 randomPos = {(float)GetRandomValue(0, Constants::SCREEN_WIDTH), (float)GetRandomValue(0, Constants::SCREEN_HEIGHT)};
        while (CheckCollisionCircles(randomPos, ufoTexture.width / 2, mPlayer.getPosition(), mPlayer.getTexture().width / 2)) {
            randomPos = {(float)GetRandomValue(0, Constants::SCREEN_WIDTH), (float)GetRandomValue(0, Constants::SCREEN_HEIGHT)};
        }
        this->mUfos.push_back(randomPos);
    }
}

void PlayScene::spawnUFO() {
    spawnUFOs(1);
}
