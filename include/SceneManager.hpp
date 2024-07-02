#pragma once

#include "raylib.h"

class StartScene;
class PlayScene;
class EndScene;

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

    ScreenState mCurrentScene;
    StartScene* mStartScene;
    PlayScene* mPlayScene;
    EndScene* mEndScene;

};
