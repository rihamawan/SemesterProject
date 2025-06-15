#include "RectangularObstacle.h"

RectangularObstacle::RectangularObstacle(const XYCoord& pos, float w, float h): Obstacle(pos), width(w), height(h){}

bool RectangularObstacle::checkCollision(const Projectile& p) {
    float px = p.getPosition().x;
    float py = p.getPosition().y;
    float closestX = clampVal(px, position.x, position.x + width);
    float closestY = clampVal(py, position.y, position.y + height);
    float dx = px - closestX;
    float dy = py - closestY;
    float r = p.getRadius();

    return (dx * dx + dy * dy) <= (r * r);
}

void RectangularObstacle::draw() const {}
