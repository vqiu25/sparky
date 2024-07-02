#include "entities/Laser.hpp"
#include "Constants.hpp"

Laser::Laser(Vector2 position, Vector2 velocity, Texture2D texture)
    : mPosition{position}
    , mVelocity{velocity}
    , mActive{true}
    , mTexture(texture) {}

void Laser::update() {
    this->mPosition.x += this->mVelocity.x * 5.0f;
    this->mPosition.y += this->mVelocity.y * 5.0f;
    if (this->mPosition.x < 0 || this->mPosition.x > Constants::SCREEN_WIDTH || this->mPosition.y < 0 || this->mPosition.y > Constants::SCREEN_HEIGHT) {
        this->mActive = false;
    }
}

void Laser::draw() {
    DrawTexture(this->mTexture, this->mPosition.x, this->mPosition.y, WHITE);
}

bool Laser::isActive() const {
    return mActive;
}
