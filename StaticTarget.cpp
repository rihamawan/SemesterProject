#include "StaticTarget.h"
StaticTarget::StaticTarget(const XYCoord& pos, float w, float h): Target(pos, w, h, false){}

void StaticTarget::update(float) {/* because its static and is not ging to update its position */ }

void StaticTarget::draw() const {
    DrawRectangle((int)position.x, (int)position.y,(int)(width), (int)height, BLUE);
}

bool StaticTarget::checkHit(const XYCoord& pos, float radius) const {
    float px = pos.x;
    float py = pos.y;
    float closestX = clampVal(px, position.x, position.x + width);
    float closestY = clampVal(py, position.y, position.y + height);

    float dx = px - closestX;
    float dy = py - closestY;

    return (dx * dx + dy * dy <= radius * radius);
}
