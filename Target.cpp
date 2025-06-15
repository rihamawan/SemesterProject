#include "Target.h"
Target::Target(const XYCoord& pos, float w, float h,bool a): position(pos), width(w), height(h), destroyed(false){}
Target::~Target() = default;
