#pragma once

class SceneManager;

class Scene {
protected:
    SceneManager* mSceneManager;

public:
    explicit Scene(SceneManager* sceneManager) : mSceneManager(sceneManager) {}
    virtual ~Scene() {}
    virtual void update() = 0;
    virtual void draw() = 0;
};
