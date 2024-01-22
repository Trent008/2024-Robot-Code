// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "math.h"


namespace angleMath {
    // limit the given angle to -pi to pi radians
    void wrap(float &angle) {
        angle = fmod(angle + M_PI, 2.0f * M_PI) - M_PI;
    }
}

