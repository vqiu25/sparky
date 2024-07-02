#pragma once

#include "raylib.h"
#include "scenes/Screen.hpp"
#include "scenes/StartScreen.hpp"
#include "scenes/PlayScreen.hpp"

class Game {
private:
    StartScreen mStartScreen;
    PlayScreen mPlayingScreen;
    Screen* mCurrentScreen;

    void switchToScreen(Screen* screen);

public:
    Game();
    ~Game();

    void run();
};