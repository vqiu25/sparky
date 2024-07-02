#pragma once

class SceneManager;

class Scene {
public:
    virtual ~Scene() {}
    virtual void update() = 0;
    virtual void draw() = 0;
};
