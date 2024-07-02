#pragma once

#include "raylib.h"

class Scene;

enum ScreenState {
    START,
    PLAY,
    END
};

class SceneManager {
public:
    SceneManager();
    ~SceneManager();
    void run();

    void SetScreenState(ScreenState state);

private:
    void update();
    void draw();
    void loadScene(ScreenState state);
    void unloadScene();

    ScreenState mCurrentScene;
    Scene* mCurrentScenePtr;
};

