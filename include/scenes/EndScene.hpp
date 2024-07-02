#pragma once

#include "Scene.hpp"

class SceneManager;

class EndScene : public Scene {
public:
    explicit EndScene(SceneManager* gameManager);
    void update() override;
    void draw() override;

private:
    SceneManager* gameManager;
};

