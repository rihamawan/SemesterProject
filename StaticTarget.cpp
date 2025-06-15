#include "StaticTarget.h"
StaticTarget::StaticTarget(const XYCoord& pos, float w, float h): Target(pos, w, h){}

void StaticTarget::update(float) {/* because its static and is not ging to update its position */ }

bool StaticTarget::checkHit(const Projectile& p) {
    // 1) Find closest point in rectangle to projectile center
    float px = p.getPosition().x;
    float py = p.getPosition().y;
    float closestX = clampVal(px, position.x, position.x + width);
    float closestY = clampVal(py, position.y, position.y + height);

    // 2) Compute distance squared
    float dx = px - closestX;
    float dy = py - closestY;
    float r = p.getRadius();

    // 3) If overlap, mark destroyed
    if (dx * dx + dy * dy <= r * r) {
        destroyed = true;
        return true;
    }
    return false;
}
