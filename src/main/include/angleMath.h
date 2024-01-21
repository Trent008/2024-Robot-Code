#pragma once
#include "math.h"

// return the difference between angle1 and angle2 limited to -180 to 180 degrees
float angleDifference(float angle1, float angle2) {
    float res = angle1 - angle2;
    if (res < -180) {
        res += 360;
    }
    if (res > 180) {
        res -= 360;
    }
    return res;
}