#pragma once

#include "Scene.hpp"
#include "entities/Spaceship.hpp"

class SceneManager;

class PlayScene : public Scene {
public:
    explicit PlayScene(SceneManager* sceneManager);
    ~PlayScene();

    void update() override;
    void draw() override;

private:
    Spaceship mPlayer;
    Texture2D mBackgroundTexture;
    Vector2 mBackgroundOffset;
};
