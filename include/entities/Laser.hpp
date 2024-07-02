#pragma once

#include "raylib.h"

class Laser {
private:
    Vector2 mPosition;
    Vector2 mVelocity;
    bool mActive;
    Texture2D mTexture;

public:
    Laser(Vector2 position, Vector2 velocity, bool active, Texture2D texture);

    void update();
    void draw();
};