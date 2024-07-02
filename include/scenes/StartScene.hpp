#pragma once

#include "Scene.hpp"

class SceneManager;

class StartScene : public Scene {
public:
    explicit StartScene(SceneManager* sceneManager);
    void update() override;
    void draw() override;

private:
    Texture2D titleTexture;
};
