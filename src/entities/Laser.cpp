#include "entities/Laser.hpp"
#include "Constants.hpp"

Laser::Laser(Vector2 position, Vector2 velocity, Texture2D texture)
    : mPosition{position}
    , mVelocity{velocity}
    , mActive{true}
    , mTexture(texture)
    , mRotation{atan2f(mVelocity.y, mVelocity.x) * RAD2DEG - 90.0f} {}

void Laser::update() {
    this->mPosition.x += this->mVelocity.x * 5.0f;
    this->mPosition.y += this->mVelocity.y * 5.0f;
    if (this->mPosition.x < 0 || this->mPosition.x > Constants::SCREEN_WIDTH || this->mPosition.y < 0 || this->mPosition.y > Constants::SCREEN_HEIGHT) {
        this->mActive = false;
    }
}

void Laser::draw() {
    DrawTexturePro(this->mTexture, {0, 0, (float)this->mTexture.width, (float)this->mTexture.height},
                   {this->mPosition.x, this->mPosition.y, (float)this->mTexture.width, (float)this->mTexture.height},
                   {(float)this->mTexture.width / 2, (float)this->mTexture.height / 2}, this->mRotation, WHITE);
}


bool Laser::isActive() const {
    return this->mActive;
}

Vector2 Laser::getPosition() const {
    return this->mPosition;
}

void Laser::setActive(bool statement) {
    this->mActive = statement;
}
