// src/MovingTarget.cpp
#include "MovingTarget.h"
MovingTarget::MovingTarget(const XYCoord& pos, float w, float h,float spd, const XYCoord& dir) : Target(pos, w, h),speed(spd),direction(dir){}
void MovingTarget::update(float dt) {
    // Simple linear movement
    position.x += direction.x * speed * dt;
    position.y += direction.y * speed * dt;
}

bool MovingTarget::checkHit(const Projectile& p) {
    float px = p.getPosition().x;
    float py = p.getPosition().y;
    float closestX = clampVal(px, position.x, position.x + width);
    float closestY = clampVal(py, position.y, position.y + height);
    float dx = px - closestX;
    float dy = py - closestY;
    float r = p.getRadius();

    if (dx * dx + dy * dy <= r * r) {
        destroyed = true;
        return true;
    }
    return false;
}
