#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "XYCoord.h"
#include "GameException.h"
/// Simulates one shot under gravity, wind, and linear drag.
class Projectile {
public:
	static constexpr float RADIUS = 5.0f;      // radius of projectile in pixels
    static constexpr float GRAVITY = 9.8f;    // m/s²
    static constexpr float DRAG_COEF = 0.1f;    // linear drag coefficient
    Projectile() {
        position = XYCoord(0, 0);
        velocity = XYCoord(0, 0);
    }
    Projectile(const XYCoord& startPos, const XYCoord& initialVel);
    void launch(XYCoord start, float angleDeg, float power, XYCoord wind);
    void reset() { active = false; }
    void update(float dt, const XYCoord& wind);
    bool isOffScreen(int screenW = 1000, int screenH = 600) const;
    bool isActive() const { return active; }
    const XYCoord& getPosition() const { return position; }
    float getRadius()   const { return RADIUS; }
    void draw() const;
private:
    XYCoord position;
    XYCoord velocity;
    float radius = 5.0f;
    bool active = false;
};
#endif