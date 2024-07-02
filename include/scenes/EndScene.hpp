#pragma once

#include "Scene.hpp"

class SceneManager;

class EndScene : public Scene {
public:
    explicit EndScene(SceneManager* sceneManager);
    void update() override;
    void draw() override;

private:

};

