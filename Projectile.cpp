#include "Projectile.h"
#include "raylib.h"
Projectile::Projectile(const XYCoord& startPos,
    const XYCoord& initialVel)
    : position(startPos), velocity(initialVel)
{}
void Projectile::launch(XYCoord start, float angleDeg, float power, XYCoord windForce) {
    position = start;
    active = true;

    float angleRad = angleDeg * 0.0174533f;

    float speed = power / 10.0f;

    velocity.x = std::cos(angleRad) * speed + windForce.x;
    velocity.y = -std::sin(angleRad) * speed + windForce.y;
}

void Projectile::update(float dt, const XYCoord& wind) {
    if (dt <= 0.0f) {
        throw PhysicsException("Projectile::update called with non-positive dt");
    }
	if (!active) return;
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

void Projectile::draw() const {
    if (!active) return;
    DrawCircle((int)position.x, (int)position.y, radius, ORANGE);
}

bool Projectile::isOffScreen(int screenW, int screenH) const {
    return position.x < 0 || position.x > screenW
        || position.y < 0 || position.y > screenH;
}
