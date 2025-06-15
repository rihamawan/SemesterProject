#ifndef DESTRUCTION_EFFECT_H
#define DESTRUCTION_EFFECT_H
#include "XYCoord.h"

class DestructionEffect {
public:
    XYCoord position;
    float timeRemaining;

    DestructionEffect();
    DestructionEffect(const XYCoord& pos);

    void draw() const;
};
#endif