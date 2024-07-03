#include "entities/Spaceship.hpp"
#include "Constants.hpp"

Spaceship::Spaceship()
        : mPosition{(float) Constants::SCREEN_WIDTH / 2, (float) Constants::SCREEN_HEIGHT / 2}
        , mVelocity{0, 0}
        , mRotation{0}
        , mHealth{200}
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
    DrawRectangleRounded((Rectangle){(float)(this->mPosition.x - 40), (float)(this->mPosition.y + 60), 80, 10}, 1.0f, 10, WHITE);
    DrawRectangleRounded((Rectangle){(float)(this->mPosition.x - 40), (float)(this->mPosition.y + 60), (float)(this->mHealth * 0.4), 10}, 1.0f, 10, RED);
}

void Spaceship::shoot() {
    Vector2 direction = {cosf((this->mRotation - 90.0f) * DEG2RAD), sinf((this->mRotation - 90.0f) * DEG2RAD)};
    Vector2 laserPos = {mPosition.x + direction.x * ((float) mTexture.width / 2), mPosition.y + direction.y * ((float) mTexture.height / 2)};
    this->mLasers.emplace_back(laserPos, direction, mLaserTexture);
}

void Spaceship::rotateToMouse(Vector2 mousePosition) {
    Vector2 direction = {mousePosition.x - this->mPosition.x, mousePosition.y - this->mPosition.y};
    this->mRotation = atan2f(direction.y, direction.x) * RAD2DEG + 90.0f;
}

void Spaceship::move() {
    Vector2 direction = {0, 0};

    if (IsKeyDown(KEY_S)) {
        direction.y -= 12.0f; // Moves up
    }
    if (IsKeyDown(KEY_W)) {
        direction.y += 12.0f; // Moves down
    }
    if (IsKeyDown(KEY_D)) {
        direction.x -= 12.0f; // Moves left
    }
    if (IsKeyDown(KEY_A)) {
        direction.x += 12.0f; // Moves right
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

std::vector<Laser>& Spaceship::getLasers() {
    return this->mLasers;
}
