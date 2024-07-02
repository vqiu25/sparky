#include "entities/Spaceship.hpp"
#include "Constants.hpp"

Spaceship::Spaceship()
        : mPosition{Constants::SCREEN_WIDTH / 2, Constants::SCREEN_HEIGHT / 2}
        , mVelocity{0, 0}
        , mRotation{0}
        , mHealth{100}
        , mTexture{LoadTexture(Constants::SPACESHIP_PATH.c_str())}
        , mLaserTexture{LoadTexture(Constants::LASER_PATH.c_str())} {}

void Spaceship::update() {
    Vector2 mousePosition = GetMousePosition();
    rotateToMouse(mousePosition);
    move();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        shoot();
    }

    for (auto& laser : this->mLasers) {
        laser.update();
    }

    this->mLasers.erase(std::remove_if(this->mLasers.begin(), this->mLasers.end(), [](Laser& l) { return !l.isActive(); }), this->mLasers.end());
}

void Spaceship::draw() {
    DrawTexturePro(this->mTexture, {0, 0, (float)this->mTexture.width, (float)this->mTexture.height},
                   {this->mPosition.x, this->mPosition.y, (float)this->mTexture.width, (float)this->mTexture.height},
                   {(float)this->mTexture.width / 2, (float)this->mTexture.height / 2}, this->mRotation, WHITE);

    for (auto& laser : this->mLasers) {
        laser.draw();
    }

    // Draw health bar
    DrawRectangle(this->mPosition.x - 40, this->mPosition.y + 60, 80, 10, WHITE);
    DrawRectangle(this->mPosition.x - 40, this->mPosition.y + 60, this->mHealth * 0.8, 10, RED);
}

void Spaceship::shoot() {
    Vector2 direction = {cosf((this->mRotation - 90.0f) * DEG2RAD), sinf((this->mRotation - 90.0f) * DEG2RAD)};
    Vector2 laserPos = {mPosition.x + direction.x * (mTexture.width / 2), mPosition.y + direction.y * (mTexture.height / 2)};
    mLasers.push_back(Laser(laserPos, direction, mLaserTexture));
}

void Spaceship::rotateToMouse(Vector2 mousePosition) {
    Vector2 direction = {mousePosition.x - this->mPosition.x, mousePosition.y - this->mPosition.y};
    this->mRotation = atan2f(direction.y, direction.x) * RAD2DEG + 90.0f;
}

void Spaceship::move() {
    Vector2 direction = {0, 0};

    if (IsKeyDown(KEY_W)) {
        direction.x += cosf((this->mRotation + 90.0f) * DEG2RAD) * 2.0f;
        direction.y += sinf((this->mRotation + 90.0f) * DEG2RAD) * 2.0f;
    }
    if (IsKeyDown(KEY_S)) {
        direction.x += cosf((this->mRotation + 90.0f) * DEG2RAD) * -2.0f;
        direction.y += sinf((this->mRotation + 90.0f) * DEG2RAD) * -2.0f;
    }

    if (IsKeyDown(KEY_A)) {
        direction.x += cosf((this->mRotation + 180.0f) * DEG2RAD) * 2.0f;
        direction.y += sinf((this->mRotation + 180.0f) * DEG2RAD) * 2.0f;
    }
    if (IsKeyDown(KEY_D)) {
        direction.x += cosf(this->mRotation * DEG2RAD) * 2.0f;
        direction.y += sinf(this->mRotation * DEG2RAD) * 2.0f;
    }

    this->mVelocity = direction;
}

void Spaceship::takeDamage(int damage) {
    this->mHealth -= damage;
    if (this->mHealth < 0) this->mHealth = 0;
}

Vector2 Spaceship::getPosition() const {
    return this->mPosition;
}

int Spaceship::getHealth() const {
    return this->mHealth;
}

Vector2 Spaceship::getVelocity() const {
    return this->mVelocity;
}

Texture2D Spaceship::getTexture() const {
    return this->mTexture;
}

Texture2D Spaceship::getLaserTexture() const {
    return this->mLaserTexture;
}
