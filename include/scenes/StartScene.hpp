#pragma once

#include "Scene.hpp"

class SceneManager;

class StartScene : public Scene {
public:
    explicit StartScene(SceneManager* gameManager);
    void update() override;
    void draw() override;

private:
    SceneManager* gameManager;
};
