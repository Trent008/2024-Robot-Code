// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include "math.h"
#include "complex"

using namespace std;


// limit the given angle to -pi to pi radians
void wrap(float &angle) {
    while(angle > M_PI) {
        angle -= 2*M_PI;
    }
    while(angle < -M_PI) {
        angle += 2*M_PI;
    }
}

