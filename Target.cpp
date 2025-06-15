#include "Target.h"
Target::Target(const XYCoord& pos, float w, float h): position(pos), width(w), height(h), destroyed(false){}
Target::~Target() = default;
