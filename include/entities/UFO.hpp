#pragma once

#include "raylib.h"
#include "Laser.hpp"
#include <vector>

class UFO {
private:
    Vector2 mPosition;
    Vector2 mVelocity;
    float mRotation;
    int mHealth;
    Texture2D mTexture;
    Texture2D mLaserTexture;
    std::vector<Laser> mLasers;

public:
    UFO(Vector2 pos);
    void update();
    void draw();
    void shoot(Vector2 playerPosition);

    Vector2 getPosition() const;
    int getHealth() const;
    void takeDamage(int damage);

    Texture2D getTexture() const;
    Texture2D getLaserTexture() const;
};