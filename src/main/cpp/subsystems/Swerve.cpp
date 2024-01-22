// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Swerve.h"

Swerve::Swerve() = default;

// This method will be called once per scheduler run
void Swerve::Drive()
{
    complex<float> field_vel = complex<float>(drive_ctrl.GetLeftX(), -drive_ctrl.GetLeftY()) * 0.5f;
    float turn_rate = -drive_ctrl.GetRightX() * 0.5;
    float angle = gyro.GetYaw();
    complex<float> robot_vel = field_vel * polar<float>(1, angle * M_PI / 180);
    float greatest = 1;
    for (int x = 0; x < 4; x++) {
        float module_speed = abs(modules[x].GetVelocity(robot_vel, turn_rate));
        if (module_speed > greatest) {
            greatest = module_speed;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        modules[i].Set(robot_vel / greatest, turn_rate);
    }
}