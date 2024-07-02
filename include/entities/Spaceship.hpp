#pragma once

#include "raylib.h"
#include "Laser.hpp"
#include <vector>

class Spaceship {
private:
    Vector2 mPosition;
    Vector2 mVelocity;
    float mRotation;
    int mHealth;
    Texture2D mTexture;
    Texture2D mLaserTexture;
    std::vector<Laser> mLasers;

public:
    Spaceship();

    void update();
    void draw();
    void shoot();
    void rotateToMouse(Vector2 mousePosition);
    void move();
    void takeDamage(int damage);

    Vector2 getPosition() const;
    int getHealth() const;
    Vector2 getVelocity() const;
    Texture2D getTexture() const;
    Texture2D getLaserTexture() const;
};