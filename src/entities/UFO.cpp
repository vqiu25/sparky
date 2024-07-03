#include "entities/UFO.hpp"
#include "Constants.hpp"

UFO::UFO(Vector2 pos)
        : mPosition{pos}
        , mVelocity{0, 0}
        , mRotation{0}
        , mHealth{30}
        , mTexture{LoadTexture(Constants::UFO_RED_PATH.c_str())}
        , mLaserTexture{LoadTexture(Constants::LASER_RED_PATH.c_str())}
        , mSpeed{5.0f}
        , mMinDistance{200.0f}{}


void UFO::update(Vector2 playerPosition, Vector2 playerVelocity) {
    Vector2 direction = {playerPosition.x - this->mPosition.x, playerPosition.y - this->mPosition.y};
    float length = sqrtf(direction.x * direction.x + direction.y * direction.y);

    // Ensure UFOs are at a fixed distance from the player
    float speedDamping = (length < mMinDistance) ? 0.5f : 1.0f;
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
    DrawRectangleRounded((Rectangle){(float)(this->mPosition.x - 40), (float)(this->mPosition.y + 60), 80, 10}, 1.0f, 10, WHITE);
    DrawRectangleRounded((Rectangle){(float)(this->mPosition.x - 40), (float)(this->mPosition.y + 60), (float)(this->mHealth * (80.0 / 30.0)), 10}, 1.0f, 10, RED);


}

void UFO::shoot(Vector2 playerPosition) {
    Vector2 direction = {playerPosition.x - this->mPosition.x, playerPosition.y - this->mPosition.y};
    float length = sqrtf(direction.x * direction.x + direction.y * direction.y);
    direction = {direction.x / length, direction.y / length};

    // Introduce more significant inaccuracy
    float inaccuracy = 0.3f; // Increase the inaccuracy
    direction.x += (float) GetRandomValue(-100, 100) / 100.0f * inaccuracy;
    direction.y += (float) GetRandomValue(-100, 100) / 100.0f * inaccuracy;

    // Normalise direction again after adding inaccuracy
    length = sqrtf(direction.x * direction.x + direction.y * direction.y);
    direction = {direction.x / length, direction.y / length};

    float laserSpeed = 0.3f;
    Vector2 laserVelocity = {direction.x * laserSpeed, direction.y * laserSpeed};

    Vector2 laserPos = {this->mPosition.x + direction.x * ((float) this->mTexture.width / 2), this->mPosition.y + direction.y * ((float) this->mTexture.height / 2)};
    this->mLasers.emplace_back(laserPos, laserVelocity, this->mLaserTexture);
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

std::vector<Laser>& UFO::getLasers() {
    return this->mLasers;
}

