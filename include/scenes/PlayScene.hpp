#pragma once

#include "Scene.hpp"

class SceneManager;

class PlayScene : public Scene {
public:
    explicit PlayScene(SceneManager* sceneManager);
    void update() override;
    void draw() override;

private:
    int framesCounter;
};
