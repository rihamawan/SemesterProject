#ifndef XYCOORD_H
#define XYCOORD_H
struct XYCoord {
    float x = 0.0f;
    float y = 0.0f;

    // Default constructor
    XYCoord() = default;
    // Parameterized constructor
    XYCoord(float _x, float _y) : x(_x), y(_y) {}
};
#endif
