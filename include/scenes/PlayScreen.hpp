#pragma once

#include "Screen.hpp"

class PlayScreen : public Screen {
private:

public:
    PlayScreen(Game* game);

    void update() override;
    void draw() override;
};