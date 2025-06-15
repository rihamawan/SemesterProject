// include/StaticTarget.h
#ifndef STATIC_TARGET_H
#define STATIC_TARGET_H
#include "Target.h"
class StaticTarget : public Target {
public:
    StaticTarget(const XYCoord& pos, float w, float h);
    void update(float dt) override;              
    bool checkHit(const Projectile& p) override;  

};
#endif 


