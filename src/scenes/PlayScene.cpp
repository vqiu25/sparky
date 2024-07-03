#include "scenes/PlayScene.hpp"
#include "SceneManager.hpp"
#include "Constants.hpp"

PlayScene::PlayScene(SceneManager* sceneManager)
        : Scene(sceneManager)
        , mPlayer{}
        , mBackgroundTexture{LoadTexture(Constants::BACKGROUND_PATH.c_str())}
        , mBackgroundOffset{0, 0}
        , mUfos{}
        , mSpawnTimer{0} {}

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

    mBackgroundOffset.x += mPlayer.getVelocity().x * 0.8f;
    mBackgroundOffset.y += mPlayer.getVelocity().y * 0.8f;

    // Wrap background offset
    if (mBackgroundOffset.x > (float) mBackgroundTexture.width) mBackgroundOffset.x = 0;
    if (mBackgroundOffset.x < (float) -mBackgroundTexture.width) mBackgroundOffset.x = (float) mBackgroundTexture.width;
    if (mBackgroundOffset.y > (float) mBackgroundTexture.height) mBackgroundOffset.y = 0;
    if (mBackgroundOffset.y < (float) -mBackgroundTexture.height) mBackgroundOffset.y = (float) mBackgroundTexture.height;

    // Update each UFO and their relative movement to the player
    for (auto& ufo : mUfos) {
        ufo.update(mPlayer.getPosition(), mPlayer.getVelocity());
        // Randomly make UFOs shoot at the player
        if (GetRandomValue(0, 100) < 2) {
            ufo.shoot(mPlayer.getPosition());
        }
    }

    // Collision detection between player and UFO lasers
    for (auto& ufo : mUfos) {
        for (auto& laser : ufo.getLasers()) {
            if (CheckCollisionCircles(laser.getPosition(), 3, mPlayer.getPosition(), (float) mPlayer.getTexture().width / 2)) {
                mPlayer.takeDamage(10);  // Assume each hit takes 10 health points
                laser.setActive(false);  // Deactivate the laser after hitting
            }
        }
    }

    // Collision detection between lasers and UFOs
    for (auto& laser : mPlayer.getLasers()) {
        for (auto& ufo : mUfos) {
            if (CheckCollisionCircles(laser.getPosition(), 3, ufo.getPosition(), (float) ufo.getTexture().width / 2)) {
                ufo.takeDamage(10);
                laser.setActive(false);
            }
        }
    }

    // Remove inactive lasers from the spaceship
    std::vector<Laser>& playerLasers = mPlayer.getLasers(); // Assuming getLasers() returns a reference
    playerLasers.erase(std::remove_if(playerLasers.begin(), playerLasers.end(), [](const Laser& laser) {
        return !laser.isActive();
    }), playerLasers.end());

    // Update each UFO and remove inactive lasers within each UFO
    for (auto& ufo : mUfos) {
        ufo.update(mPlayer.getPosition(), mPlayer.getVelocity());
        std::vector<Laser>& lasers = ufo.getLasers();
        lasers.erase(std::remove_if(lasers.begin(), lasers.end(), [](const Laser& laser) {
            return !laser.isActive();
        }), lasers.end());
    }

    // Remove dead UFOs
    mUfos.erase(std::remove_if(mUfos.begin(), mUfos.end(), [](UFO& u) { return u.getHealth() <= 0; }), mUfos.end());

    // Spawn new UFOs every 350 frames
    mSpawnTimer++;
    if (mSpawnTimer > 350) {
        spawnUFO();
        mSpawnTimer = 0;
    }

    // Player loses
    if (mPlayer.getHealth() <= 0) {
        this->mSceneManager->SetScreenState(END);
    }
}

void PlayScene::draw() {
    for (int x = -1; x <= Constants::SCREEN_WIDTH / mBackgroundTexture.width; ++x) {
        for (int y = -1; y <= Constants::SCREEN_HEIGHT / mBackgroundTexture.height; ++y) {
            DrawTexture(mBackgroundTexture, (int) mBackgroundOffset.x + x * mBackgroundTexture.width, (int) mBackgroundOffset.y + y * mBackgroundTexture.height, WHITE);
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
        Vector2 randomPos;

        int side = GetRandomValue(0, 3); // Randomly choose a side (0: top, 1: bottom, 2: left, 3: right)

        switch (side) {
            case 0: // Top
                randomPos = {
                        static_cast<float>(GetRandomValue(0, Constants::SCREEN_WIDTH)),
                        -static_cast<float>(ufoTexture.height) // Spawn just above the top edge
                };
                break;
            case 1: // Bottom
                randomPos = {
                        static_cast<float>(GetRandomValue(0, Constants::SCREEN_WIDTH)),
                        static_cast<float>(Constants::SCREEN_HEIGHT) // Spawn just below the bottom edge
                };
                break;
            case 2: // Left
                randomPos = {
                        -static_cast<float>(ufoTexture.width), // Spawn just to the left of the left edge
                        static_cast<float>(GetRandomValue(0, Constants::SCREEN_HEIGHT))
                };
                break;
            case 3: // Right
                randomPos = {
                        static_cast<float>(Constants::SCREEN_WIDTH), // Spawn just to the right of the right edge
                        static_cast<float>(GetRandomValue(0, Constants::SCREEN_HEIGHT))
                };
                break;
            default:
                break;
        }

        // Add new UFO to the list, assuming UFO constructor takes position and texture
        this->mUfos.emplace_back(randomPos);
    }
}

void PlayScene::spawnUFO() {
    spawnUFOs(1);
}

