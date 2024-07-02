#pragma once

#include "raylib.h"
#include "Constants.hpp"

class SceneManager;

class Scene {
protected:
    SceneManager* mSceneManager;

public:
    explicit Scene(SceneManager* sceneManager) : mSceneManager(sceneManager) {}
    virtual ~Scene() = default;
    virtual void update() = 0;
    virtual void draw() = 0;
};
