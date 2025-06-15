#ifndef RECTANGULAR_OBSTACLE_H
#define RECTANGULAR_OBSTACLE_H
#include "Obstacle.h"
class RectangularObstacle : public Obstacle {
public:
    RectangularObstacle(const XYCoord& pos, float w, float h);
    bool checkCollision(const Projectile& p) override;
    void draw() const override;

private:
    float width, height;
};
#endif