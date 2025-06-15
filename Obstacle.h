#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "XYCoord.h"
#include "Projectile.h"
#include "raylib.h"
class Obstacle {
public:
    Obstacle(const XYCoord& pos) :position(pos) {}
    virtual ~Obstacle()=default;
    virtual bool checkCollision(const Projectile& p) = 0;
    virtual void draw() const = 0;

protected:
    XYCoord position;
    static float clampVal(float v, float lo, float hi) {
        if (v < lo)   return lo;
        if (v > hi)   return hi;
        return v;
    }
};
#endif