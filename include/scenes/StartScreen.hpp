#pragma once

#include "Screen.hpp"

class StartScreen : public Screen {
private:

public:
    StartScreen(Game* game);

    void update() override;
    void draw() override;
};