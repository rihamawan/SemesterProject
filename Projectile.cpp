#include "Projectile.h"
Projectile::Projectile(const XYCoord& startPos,
    const XYCoord& initialVel)
    : position(startPos), velocity(initialVel)
{}

void Projectile::update(float dt, const XYCoord& wind) {
    if (dt <= 0.0f) {
        throw PhysicsException("Projectile::update called with non-positive dt");
    }
    // 1) Apply wind & gravity 
    velocity.x += wind.x * dt;
    velocity.y += (GRAVITY + wind.y) * dt;

    // 2) linear drag: This always opposes the current velocity.
    velocity.x -= DRAG_COEF * velocity.x * dt;
    velocity.y -= DRAG_COEF * velocity.y * dt;

    // 3) Integrate next position
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
}

bool Projectile::isOffScreen(int screenW, int screenH) const {
    return position.x < 0 || position.x > screenW
        || position.y < 0 || position.y > screenH;
}
