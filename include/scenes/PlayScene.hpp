#pragma once

#include "Scene.hpp"
#include "entities/Spaceship.hpp"
#include "entities/UFO.hpp"

class SceneManager;

class PlayScene : public Scene {
public:
    explicit PlayScene(SceneManager* sceneManager);
    ~PlayScene();

    void update() override;
    void draw() override;
    void spawnUFO();
    void spawnUFOs(int count);
    void cleanupLasers();

private:
    Spaceship mPlayer;
    Texture2D mBackgroundTexture;
    Vector2 mBackgroundOffset;
    std::vector<UFO> mUfos;
    int mSpawnTimer;
};
