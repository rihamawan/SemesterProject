#include "CircularObstacle.h"

CircularObstacle::CircularObstacle(const XYCoord& center, float r) : Obstacle(center), radius(r){}

bool CircularObstacle::checkCollision(const Projectile& p) {
    float dx = p.getPosition().x - position.x;
    float dy = p.getPosition().y - position.y;
    float distSq = dx * dx + dy * dy;
    float combinedR = radius + p.getRadius();
    return distSq <= (combinedR * combinedR);
}

void CircularObstacle::draw() const {
    DrawCircle((int)(position.x), (int)(position.y),
        radius, DARKGRAY);
}
