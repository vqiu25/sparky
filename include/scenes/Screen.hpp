#pragma once

#include "raylib.h"
#include "Game.hpp"

class Screen {
protected:
    Game* mGame;

public:
    Screen(Game* game) {}
    virtual ~Screen() {}

    virtual void update() = 0;
    virtual void draw() = 0;
};