// src/MovingTarget.cpp
#include "MovingTarget.h"
MovingTarget::MovingTarget(const XYCoord& pos, float w, float h,float spd, const XYCoord& dir) : Target(pos, w, h,false),speed(spd),direction(dir){}
void MovingTarget::update(float dt) {
    // Simple linear movement
    position.x += direction.x * speed * dt;
    position.y += direction.y * speed * dt;
}

void MovingTarget::draw() const {
    DrawRectangle((int)(position.x), (int)(position.y), (int)(width), (int)(height), RED);
}

bool MovingTarget::checkHit(const XYCoord& pos, float radius) const {
    float px = pos.x;
    float py = pos.y;
    float closestX = clampVal(px, position.x, position.x + width);
    float closestY = clampVal(py, position.y, position.y + height);

    float dx = px - closestX;
    float dy = py - closestY;
    return (dx * dx + dy * dy <= radius * radius);
}