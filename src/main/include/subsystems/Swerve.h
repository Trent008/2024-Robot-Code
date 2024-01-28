// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "subsystems/Module.h"
#include "AHRS.h"
class Swerve
{
public:
	void set(complex<float> driveV, float turningV) {
		angle = -gyro.GetYaw()*M_PI/180;
		driveV *= polar<float>(1, -angle);
		// normalize module speeds
		float fastest = 1;
		for (auto module : modules) {
			float moduleSpeed = abs(module.getV(driveV, turningV));
			if (moduleSpeed > fastest) {
				fastest = moduleSpeed;
			}
		}
		// drive the modules
		for (auto module : modules) {
			module.set(driveV/fastest, turningV/fastest);
		}
	}
private:
	Module modules[4] = {
		Module(1, complex<float>(-17.75, 25)),
		Module(2, complex<float>(-17.75, -25)),
		Module(3, complex<float>(17.75, 25)),
		Module(4, complex<float>(17.75, -25))};
	AHRS gyro{frc::SPI::Port::kMXP};
	float angle;
};
