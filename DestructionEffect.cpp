#include "DestructionEffect.h"
#include "raylib.h"

DestructionEffect::DestructionEffect() : position(0, 0), timeRemaining(1.0f) {}

DestructionEffect::DestructionEffect(const XYCoord& pos)
    : position(pos), timeRemaining(1.0f) {}

void DestructionEffect::draw() const {
    DrawCircle((int)position.x, (int)position.y, 25, RED);
    DrawText("*", (int)position.x - 10, (int)position.y - 10, 20, BLACK);
}