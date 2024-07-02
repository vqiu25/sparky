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
    float mSpeed;
    float mMinDistance;

public:
    UFO(Vector2 pos);
    void update(Vector2 playerPosition, Vector2 playerVelocity);
    void draw();
    void shoot(Vector2 playerPosition);

    Vector2 getPosition() const;
    int getHealth() const;
    void takeDamage(int damage);

    Texture2D getTexture() const;
    Texture2D getLaserTexture() const;
    std::vector<Laser> getLasers() const;
};