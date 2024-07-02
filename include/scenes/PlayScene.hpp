#pragma once

#include "Scene.hpp"

class SceneManager;

class PlayScene : public Scene {
public:
    explicit PlayScene(SceneManager* gameManager);
    void update() override;
    void draw() override;

private:
    SceneManager* gameManager;
    int framesCounter;
};
