// include/Target.h
#ifndef TARGET_H
#define TARGET_H
#include "XYCoord.h"
#include "Projectile.h"
class Target {
public:
    Target(const XYCoord& pos, float w, float h);
    virtual ~Target();

    /// Move the target 
    virtual void update(float dt) = 0;

    virtual bool checkHit(const Projectile& p) = 0;

    bool isDestroyed() const { return destroyed; }

    void setDestroyed(bool d) { destroyed = d; };

    const XYCoord& getPosition() const { return position; }

protected:
    XYCoord position;
    float   width, height;
    bool    destroyed = false;
    static float clampVal(float v, float lo, float hi) {
        if (v < lo)   return lo;
        if (v > hi)   return hi;
        return v;
    }
};
#endif