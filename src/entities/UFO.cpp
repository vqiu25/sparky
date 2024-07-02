#include "entities/UFO.hpp"
#include "Constants.hpp"

UFO::UFO(Vector2 pos)
        : mPosition{pos}
        , mVelocity{0, 0}
        , mRotation{0}
        , mHealth{50}
        , mTexture{LoadTexture(Constants::UFO_RED_PATH.c_str())}
        , mLaserTexture{LoadTexture(Constants::LASER_RED_PATH.c_str())}
        , mSpeed{5.0f}
        , mMinDistance{200.0f}{}


void UFO::update(Vector2 playerPosition, Vector2 playerVelocity) {
    Vector2 direction = {playerPosition.x - this->mPosition.x, playerPosition.y - this->mPosition.y};
    float length = sqrtf(direction.x * direction.x + direction.y * direction.y);

    // Decrease speed as it nears the player to give the player a chance to escape
    float speedDamping = (length < mMinDistance) ? 0.5f : 1.0f;

    // Correcting the relative velocity to pursue the player correctly
    Vector2 relativeVelocity = {playerVelocity.x * 0.5f, playerVelocity.y * 0.5f};

    if (length > mMinDistance) {
        direction = {direction.x / length, direction.y / length};
        this->mVelocity = {direction.x * this->mSpeed * speedDamping + relativeVelocity.x,
                           direction.y * this->mSpeed * speedDamping + relativeVelocity.y};
    } else {
        this->mVelocity = relativeVelocity;
    }

    this->mPosition.x += this->mVelocity.x;
    this->mPosition.y += this->mVelocity.y;
    this->mRotation = atan2f(direction.y, direction.x) * RAD2DEG;

    // Update existing lasers and remove inactive ones
    for (auto& laser : this->mLasers) {
        laser.update();
    }
    this->mLasers.erase(std::remove_if(this->mLasers.begin(), this->mLasers.end(), [](Laser& l) { return !l.isActive(); }), this->mLasers.end());
}

void UFO::draw() {
    DrawTexturePro(this->mTexture, {0, 0, (float)this->mTexture.width, (float)this->mTexture.height},
                   {this->mPosition.x, this->mPosition.y, (float)this->mTexture.width, (float)this->mTexture.height},
                   {(float)this->mTexture.width / 2, (float)this->mTexture.height / 2}, this->mRotation, WHITE);

    for (auto& laser : this->mLasers) {
        laser.draw();
    }

    // Draw health bar
    DrawRectangle(this->mPosition.x - 40, this->mPosition.y + 30, 80, 10, DARKGRAY);
    DrawRectangle(this->mPosition.x - 40, this->mPosition.y + 30, this->mHealth * 0.8, 10, RED);
}

void UFO::shoot(Vector2 playerPosition) {
    Vector2 direction = {playerPosition.x - this->mPosition.x, playerPosition.y - this->mPosition.y};
    float length = sqrtf(direction.x * direction.x + direction.y * direction.y);
    direction = {direction.x / length, direction.y / length};

    Vector2 laserPos = {this->mPosition.x + direction.x * (this->mTexture.width / 2), this->mPosition.y + direction.y * (this->mTexture.height / 2)};
    this->mLasers.push_back(Laser{laserPos, direction, this->mLaserTexture});
}

Vector2 UFO::getPosition() const {
    return this->mPosition;
}

int UFO::getHealth() const {
    return this->mHealth;
}

void UFO::takeDamage(int damage) {
    this->mHealth -= damage;
    if (this->mHealth < 0) this->mHealth = 0;
}

Texture2D UFO::getTexture() const {
    return this->mTexture;
}

Texture2D UFO::getLaserTexture() const {
    return this->mLaserTexture;
}

std::vector<Laser> UFO::getLasers() const {
    return this->mLasers;
}

