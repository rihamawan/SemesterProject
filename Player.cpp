#include "Player.h"
#include <cmath>

Player::Player(const MyString& name_, const XYCoord& startPos_) : name(name_), score(0), angle(45.0f), power(50.0f), position(startPos_){}
Projectile Player::fire() const {
    // Convert degrees→radians
    float rad = angle * (3.14159f / 180.0f);

    XYCoord vel{
        std::cos(rad) * power,
        std::sin(rad) * power
    };

    return Projectile(position, vel);
}

void Player::setAngle(float a) {
    if (a < 0.0f)   a = 0.0f;
    if (a > MAX_ANGLE) a = MAX_ANGLE;
    angle = a;
}

void Player::setPower(float p) {
    if (p < 0.0f)       p = 0.0f;
    if (p > MAX_POWER) p = MAX_POWER;
    power = p;
}

void Player::addScore(int pts) {
    score += pts;
}
