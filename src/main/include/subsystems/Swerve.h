// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "subsystems/SwerveModule.h"
#include "AHRS.h"
class Swerve
{
public:
	Swerve();

	SwerveModule modules[4] = {
		SwerveModule(1, complex<float>(-1, 1)),
		SwerveModule(2, complex<float>(-1, -1)),
		SwerveModule(3, complex<float>(1, 1)),
		SwerveModule(4, complex<float>(1, -1))};

	/**
	 * drives the swerve with an XBox controller
	 */
	void Set(complex<float> field_vel, float turn_rate);

private:
	// Components (e.g. motor controllers and sensors) should generally be
	// declared private and exposed only through public methods.
	AHRS gyro{frc::SPI::Port::kMXP};
};
