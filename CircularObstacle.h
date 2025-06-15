#ifndef CIRCULAR_OBSTACLE_H
#define CIRCULAR_OBSTACLE_H
#include "Obstacle.h"
class CircularObstacle : public Obstacle {
public:
    CircularObstacle(const XYCoord& center, float radius);

    bool checkCollision(const Projectile& p) override;
    void draw() const override;

private:
    float radius;
};
#endif
