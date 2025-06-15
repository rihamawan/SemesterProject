#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "XYCoord.h"
#include "GameException.h"
/// Simulates one shot under gravity, wind, and linear drag.
class Projectile {
public:
    static constexpr float RADIUS = 5.0f;    // for collisions / drawing
    static constexpr float GRAVITY = 9.8f;    // m/s²
    static constexpr float DRAG_COEF = 0.1f;    // linear drag coefficient

    Projectile(const XYCoord& startPos, const XYCoord& initialVel);
    void update(float dt, const XYCoord& wind);
    bool isOffScreen(int screenW, int screenH) const;
    const XYCoord& getPosition() const { return position; }
    float getRadius()   const { return RADIUS; }

private:
    XYCoord position;
    XYCoord velocity;
};
#endif