#pragma once

#include "raylib.h"

class Laser {
private:
    Vector2 mPosition;
    Vector2 mVelocity;
    bool mActive;
    Texture2D mTexture;
    float mRotation;

public:
    Laser(Vector2 position, Vector2 velocity, Texture2D texture);

    void update();
    void draw();
    bool isActive() const;
    Vector2 getPosition() const;
    void setActive(bool statement);
};