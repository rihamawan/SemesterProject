#ifndef MOVINGTARGET_H
#define MOVINGTARGET_H
#include "Target.h"
#include "XYCoord.h"
class MovingTarget : public Target {
public:
    MovingTarget(const XYCoord& pos, float w, float h, float speed, const XYCoord& dir);
    void update(float dt) override;               
    bool checkHit(const Projectile& p) override;  

private:
    float   speed;      // units per second
    XYCoord direction;  // e.g. {1,0} moves right
  
};
#endif 
