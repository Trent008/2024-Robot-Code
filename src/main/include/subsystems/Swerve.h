// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "subsystems/SwerveModule.h"
#include "AHRS.h"
#include "frc/XboxController.h"

class Swerve : public frc2::SubsystemBase
{
public:
	Swerve();

	SwerveModule modules[4] = {
		SwerveModule(1, complex<float>(-1, 1)),
		SwerveModule(2, complex<float>(-1, -1)),
		SwerveModule(3, complex<float>(1, 1)),
		SwerveModule(4, complex<float>(1, -1))};

	/**
	 * Will be called periodically whenever the CommandScheduler runs.
	 */
	void Drive();

private:
	// Components (e.g. motor controllers and sensors) should generally be
	// declared private and exposed only through public methods.
	frc::XboxController drive_ctrl{0};
	AHRS gyro{frc::SPI::Port::kMXP};
};
