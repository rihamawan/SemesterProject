#pragma once
#include "XYCoord.h"
#include "MyString.h"
#include "Projectile.h"

// Represents one shooter: remembers angle/power & spawns projectiles.
class Player {
public:
    static constexpr float MAX_POWER = 100.0f;  // percent
    static constexpr float MAX_ANGLE = 90.0f;  // degrees

    Player(const MyString& name_, const XYCoord& startPos_);
    Projectile fire() const;
    void setAngle(float a);

    void setPower(float p);
    void addScore(int pts);

    float       getAngle() const { return angle; }
    float       getPower() const { return power; }
    int         getScore() const { return score; }
    const MyString& getName() const { return name; }
	const XYCoord& getPosition() const { return position; }

private:
    MyString   name;
    int     score;
    float   angle;      // in degrees
    float   power;      // 0–100
    XYCoord position;   // fixed firing point


};
